#ifndef VMATH_HNSW_H
#define VMATH_HNSW_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <random>
#include <stdexcept>
#include <unordered_set>
#include <vector>

#include "types.h"
#include "vect.h"

namespace nobridge::vmath {

    // --- HNSW Core Implementation ---
    template <typename T, std::size_t N>
    class HNSW {
       public:
        // --- Constructor ---
        HNSW(size_t M = 16, size_t efConstruction = 200)
            : m_M(M), m_efConstruction(efConstruction), m_rng(std::random_device{}()) {
            // `m_level_mult` is calculated based on M to ensure a good layer distribution.
            m_level_mult = 1.0 / log(1.0 * m_M);
        }

        // Adds a new vector (point) to the HNSW graph.
        void addPoint(const mika::VecT<T, N>& point, UIntID label) {
            if (point.size() != N) {
                throw std::invalid_argument("Point dimension does not match index dimension.");
            }

            // Create the new node.
            m_nodes.resize(std::max(m_nodes.size(), label + 1));
            m_nodes[label].data = point;

            if (m_max_layer == -1) {  // This is the first point added.
                m_entry_point = label;
                m_max_layer = 0;
                m_nodes[label].connections.resize(1);
                return;
            }

            // --- Insertion Algorithm ---
            int new_level = getRandomLevel();
            m_nodes[label].connections.resize(new_level + 1);

            UIntID current_ep = m_entry_point;

            // 1. Top-down search to find entry points for each layer.
            for (int layer = m_max_layer; layer > new_level; --layer) {
                auto result_queue = searchLayer(point, {current_ep}, 1, layer);
                current_ep = result_queue.top().second;
            }

            // 2. From new_level down to 0, find neighbors and connect them.
            for (int layer = std::min(new_level, m_max_layer); layer >= 0; --layer) {
                auto neighbors_queue = searchLayer(point, {current_ep}, m_efConstruction, layer);

                // Convert priority queue to a vector for easier manipulation.
                std::vector<std::pair<float, UIntID>> neighbors;
                while (!neighbors_queue.empty()) {
                    neighbors.push_back(neighbors_queue.top());
                    neighbors_queue.pop();
                }

                // Select the best M neighbors.
                if (neighbors.size() > m_M) {
                    neighbors.resize(m_M);
                }

                // Connect the new node to its M best neighbors.
                for (const auto& neighbor : neighbors) {
                    m_nodes[label].connections[layer].push_back(neighbor.second);
                }

                // Connect the M neighbors back to the new node.
                for (const auto& neighbor : neighbors) {
                    auto& neighbor_connections = m_nodes[neighbor.second].connections[layer];
                    neighbor_connections.push_back(label);

                    // If a neighbor now has > M connections, prune the furthest one.
                    if (neighbor_connections.size() > m_M) {
                        float max_dist = -1.0f;
                        UIntID furthest_neighbor = -1;
                        for (UIntID conn_label : neighbor_connections) {
                            float dist =
                                L2Sqr(m_nodes[neighbor.second].data, m_nodes[conn_label].data);
                            if (dist > max_dist) {
                                max_dist = dist;
                                furthest_neighbor = conn_label;
                            }
                        }
                        // Remove the furthest connection.
                        neighbor_connections.erase(
                            std::remove(neighbor_connections.begin(), neighbor_connections.end(),
                                        furthest_neighbor),
                            neighbor_connections.end());
                    }
                }
                // Update the entry point for the next lower layer.
                if (!neighbors.empty()) {
                    current_ep = neighbors.back().second;  // Farthest in the selected set
                }
            }

            // Update the global entry point if the new node is on a higher layer.
            if (new_level > m_max_layer) {
                m_max_layer = new_level;
                m_entry_point = label;
            }
        }

        // Searches for the `k` nearest neighbors to a query vector.
        std::priority_queue<std::pair<float, UIntID>> searchKnn(const mika::VecT<T, N>& query,
                                                                size_t k) {
            if (m_max_layer == -1) {  // Empty graph
                return {};
            }

            UIntID current_ep = m_entry_point;

            // 1. Top-down search to find the entry point on the base layer.
            for (int layer = m_max_layer; layer > 0; --layer) {
                auto result_queue = searchLayer(query, {current_ep}, 1, layer);
                current_ep = result_queue.top().second;
            }

            // 2. Perform the final, most thorough search on the base layer (layer 0).
            return searchLayer(query, {current_ep}, k, 0);
        }

       private:
        // --- Data Structures ---

        // Represents a node in the graph.
        struct Node {
            mika::VecT<T, N> data;
            // A list of neighbors for each layer the node is on.
            // `connections[layer][neighbor_index]`
            std::vector<std::vector<UIntID>> connections;
        };

        // Stores all nodes in the graph. The index in this vector is the node's label.
        std::vector<Node> m_nodes;
        // The entry point for searches. Always points to the node in the highest layer.
        UIntID m_entry_point = 0;
        // The current highest layer in the graph.
        int m_max_layer = -1;

        // --- HNSW Parameters ---

        // `M`: The max number of connections a node can have on a layer.
        size_t m_M;
        // `efConstruction`: The size of the dynamic candidate list during insertion.
        size_t m_efConstruction;
        // Normalization factor for random level generation.
        double m_level_mult;
        // Random number generator for level assignment.
        std::mt19937 m_rng;

        // --- Private Methods ---

        // Generates a random level for a new node based on an exponential distribution.
        // Higher levels are exponentially less likely.
        int getRandomLevel() {
            std::uniform_real_distribution<double> dist(0.0, 1.0);
            return static_cast<int>(-log(dist(m_rng)) * m_level_mult);
        }

        // Searches for the `k` nearest neighbors to a query on a single layer.
        // This is the greedy search algorithm at the heart of HNSW.
        std::priority_queue<std::pair<float, UIntID>> searchLayer(
            const mika::VecT<T, N>& query, const std::unordered_set<UIntID>& entry_points, size_t k,
            int layer) {
            // Min-priority queue for results (stores {distance, label}).
            std::priority_queue<std::pair<float, UIntID>> top_k;
            // Max-priority queue for candidates to visit (stores {-distance, label}).
            std::priority_queue<std::pair<float, UIntID>> candidates;
            // Set to keep track of visited nodes to avoid redundant computations.
            std::unordered_set<UIntID> visited;

            // Initialize candidates with the entry points.
            for (auto ep : entry_points) {
                float dist = L2Sqr(query, m_nodes[ep].data);
                candidates.push({-dist, ep});
                top_k.push({dist, ep});
                visited.insert(ep);
                if (top_k.size() > k) {
                    top_k.pop();
                }
            }

            while (!candidates.empty()) {
                // Get the closest candidate.
                auto [neg_dist, curr_label] = candidates.top();
                candidates.pop();

                // If the candidate is further than the k-th best result, we can stop.
                if (-neg_dist > top_k.top().first && top_k.size() >= k) {
                    break;
                }

                // Explore the neighbors of the current node.
                for (UIntID neighbor_label : m_nodes[curr_label].connections[layer]) {
                    if (visited.find(neighbor_label) == visited.end()) {
                        visited.insert(neighbor_label);
                        float dist = L2Sqr(query, m_nodes[neighbor_label].data);

                        if (dist < top_k.top().first || top_k.size() < k) {
                            candidates.push({-dist, neighbor_label});
                            top_k.push({dist, neighbor_label});
                            if (top_k.size() > k) {
                                top_k.pop();
                            }
                        }
                    }
                }
            }
            return top_k;
        }
    };

}  // namespace nobridge::vmath

// --- Example Usage ---
/*
int main() {
    // --- Setup ---
    const int dim = 5;            // Dimension of vectors
    const int num_points = 1000;  // Number of points to index
    const int k = 5;              // Number of nearest neighbors to find

    // Create an instance of the HNSW index.
    hnswlib::HNSW index(dim, 16, 200);  // (dimension, M, efConstruction)

    // --- Data Generation and Indexing ---
    std::cout << "Generating " << num_points << " random " << dim
              << "D vectors and adding them to the index..." << std::endl;

    // Use a random number generator to create data.
    std::mt19937 rng(std::time(0));
    std::uniform_real_distribution<float> dist(0.0, 1.0);

    std::vector<hnswlib::Vector> dataset(num_points, hnswlib::Vector(dim));
    for (int i = 0; i < num_points; ++i) {
        for (int d = 0; d < dim; ++d) {
            dataset[i][d] = dist(rng);
        }
        // Add the point to the index with its index as the label.
        index.addPoint(dataset[i], i);
    }
    std::cout << "Indexing complete." << std::endl;

    // --- Searching ---
    // Create a random query vector.
    hnswlib::Vector query_vector(dim);
    for (int d = 0; d < dim; ++d) {
        query_vector[d] = dist(rng);
    }
    std::cout << "\nSearching for the " << k << " nearest neighbors to a random query vector..."
              << std::endl;

    // Perform the search.
    auto result_queue = index.searchKnn(query_vector, k);

    // --- Display Results ---
    // The result is a min-priority queue, so we need to reverse it to display from closest to
    // farthest.
    std::vector<std::pair<float, hnswlib::UIntID>> results;
    while (!result_queue.empty()) {
        results.push_back(result_queue.top());
        result_queue.pop();
    }
    std::reverse(results.begin(), results.end());

    std::cout << "Search Results (closest first):" << std::endl;
    for (const auto& result : results) {
        // The distance is squared L2, so we take the sqrt for the actual Euclidean distance.
        float distance = std::sqrt(result.first);
        hnswlib::UIntID label = result.second;
        std::cout << "  - Label: " << label << ", Distance: " << distance << std::endl;
    }

    return 0;
}
*/
#endif  // HNSW_LIB_H
