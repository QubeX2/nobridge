#ifndef VMATH_HNSW_H
#define VMATH_HNSW_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
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

        void save(const std::string index_path) {
            std::ofstream out_file(index_path, std::ios::binary | std::ios::trunc);
            if (!out_file) {
                std::cerr << "Error: Could not open file for writing: " << index_path << "\n";
                return;
            }

            // 1. Write the total number of Node objects in the vector.
            size_t num_nodes = m_nodes.size();
            out_file.write(reinterpret_cast<const char*>(&num_nodes), sizeof(num_nodes));

            // 2. Loop through and write each Node object individually.
            for (const auto& node : m_nodes) {
                this->writeNode(out_file, node);
            }

            out_file.close();
        }

        void load(const std::string index_path) {
            std::ifstream in_file(index_path, std::ios::binary);
            if (!in_file) {
                std::cerr << "Error: Could not open file for reading: " << index_path << std::endl;
                return;
            }

            // 1. Read the total number of Node objects.
            size_t num_nodes;
            in_file.read(reinterpret_cast<char*>(&num_nodes), sizeof(num_nodes));

            // 2. Resize the output vector to hold all the nodes.
            m_nodes.resize(num_nodes);

            for (size_t i = 0; i < num_nodes; ++i) {
                this->readNode(in_file, m_nodes[i]);
            }

            in_file.close();
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
                                m_nodes[neighbor.second].data.L2Sqr(m_nodes[conn_label].data);
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
        // read single node
        void readNode(std::ifstream& in, Node& node) {
            in.read(reinterpret_cast<char*>(node.data.data()), sizeof(T) * N);

            size_t num_layers;
            in.read(reinterpret_cast<char*>(&num_layers), sizeof(num_layers));
            node.connections.resize(num_layers);

            for (size_t i = 0; i < num_layers; ++i) {
                size_t num_neighbors;
                in.read(reinterpret_cast<char*>(&num_neighbors), sizeof(num_neighbors));
                node.connections[i].resize(num_neighbors);
                in.read(reinterpret_cast<char*>(node.connections[i].data()),
                        num_neighbors * sizeof(UIntID));
            }
        }

        // write single node
        void writeNode(std::ofstream& out, const Node& node) {
            out.write(reinterpret_cast<const char*>(node.data.data()), sizeof(T) * N);

            size_t num_layers = node.connections.size();
            out.write(reinterpret_cast<const char*>(&num_layers), sizeof(num_layers));

            for (const auto& layer_connections : node.connections) {
                size_t num_neighbors = layer_connections.size();
                out.write(reinterpret_cast<const char*>(&num_neighbors), sizeof(num_neighbors));
                out.write(reinterpret_cast<const char*>(layer_connections.data()),
                          num_neighbors * sizeof(UIntID));
            }
        }

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
                float dist = query.L2Sqr(m_nodes[ep].data);
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
                        float dist = query.L2Sqr(m_nodes[neighbor_label].data);

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

#endif  // HNSW_LIB_H
