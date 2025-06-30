#include <gtest/gtest.h>

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
}
