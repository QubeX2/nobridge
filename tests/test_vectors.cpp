#include <gtest/gtest.h>

#include <vector>

#include "hnsw.h"
#include "types.h"
#include "vect.h"

using namespace nobridge;

TEST(VectorTest, VectorMath1) {
    mika::VecT<float, 5> v1{3, 2, 1, 0, 0};
    mika::VecT<float, 5> v2{3, 2, 1.2, 0, 0};
    mika::VecT<float, 5> v3{3, 2, 2, 0, 0};
    mika::VecT<float, 5> v4{3, 2, 1, 1, 0};
    // std::cout << v1.
    std::cout << "Distance v1-v2:\n" << v1 << v2 << v1.distance(v2) << "\n";
    std::cout << "Distance v1-v3:\n" << v1 << v3 << v1.distance(v3) << "\n";
    std::cout << "Distance v1-v4:\n" << v1 << v4 << v1.distance(v4) << "\n";
    std::cout << "\n";
    std::cout << "Angle v1-v2:\n" << v1 << v2 << v1.angleDeg(v2) << "\n";
    std::cout << "Angle v1-v3:\n" << v1 << v3 << v1.angleDeg(v3) << "\n";
    std::cout << "Angle v1-v4:\n" << v1 << v4 << v1.angleDeg(v4) << "\n";

    std::vector<int> vectors;
    vectors.resize(10002);
    vectors[10002] = 10;
    std::cout << "Vectors! " << vectors[10002] << "\n";
}

TEST(VectorTest, HNSW_Test) {
    const int NUM_POINTS = 1000;
    const int K = 5;
    const std::size_t DIM = 5;

    vmath::HNSW<float, DIM> index{};

    std::mt19937 rng(std::time(0));
    std::uniform_real_distribution<float> dist(1.0f, 10.0f);

    // Indexing
    std::cout << "\nIndexing: " << NUM_POINTS << " vectors.\n";
    mika::VecTList<float, DIM> dataset(NUM_POINTS, mika::VecT<float, DIM>());
    for (std::size_t i = 0; i < NUM_POINTS; ++i) {
        for (std::size_t d = 0; d < DIM; ++d) {
            dataset[i][d] = dist(rng);
        }
        // Add the point to the index with its index as the label.
        index.addPoint(dataset[i], i);
    }
    std::cout << "Done Indexing\n";

    index.save("./index.bin");

    vmath::HNSW<float, DIM> index2{};
    index2.load("./index.bin");

    // --- Searching ---
    // Create a random query vector.
    mika::VecT<float, DIM> query_vector;
    for (std::size_t d = 0; d < DIM; ++d) {
        query_vector[d] = dist(rng);
    }
    std::cout << "\nQuery Vector\n";
    std::cout << query_vector << "\n";
    std::cout << "Searching for the " << K << " nearest neighbors to a random query vector..."
              << std::endl;

    // Perform the search.
    auto result_queue = index2.searchKnn(query_vector, K);

    // --- Display Results ---
    // The result is a min-priority queue, so we need to reverse it to display from closest to
    // farthest.
    std::vector<std::pair<float, UIntID>> results;
    while (!result_queue.empty()) {
        results.push_back(result_queue.top());
        result_queue.pop();
    }
    std::reverse(results.begin(), results.end());

    std::cout << "Search Results (closest first):" << std::endl;
    for (const auto& result : results) {
        // The distance is squared L2, so we take the sqrt for the actual Euclidean distance.
        float distance = std::sqrt(result.first);
        UIntID label = result.second;
        std::cout << "  - Label: " << label << ", Distance: " << distance << "\n";
        std::cout << dataset[label] << "\n";
    }
}
