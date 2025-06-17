#include <gtest/gtest.h>

#include <format>
#include <iostream>

#include "vect.h"

TEST(VectorTest, HandlesVectorMath) {
    mkrl::VecT<float, 5> vec5a{1.0, 0.0, 0.0, 0.0, 0.0};
    mkrl::VecT<float, 5> vec5b{0.0, 1.0, 0.0, 0.0, 0.0};

    // std::cout << std::format("Radian: {}, Degree: {}\n", vec5a.angle(vec5b),
    //                         vec5a.angleDeg(vec5b));

    EXPECT_EQ(vec5a.length(), 1);
    EXPECT_EQ(vec5a.angleDeg(vec5b), 90);

    // std::cout << vec5a << std::endl;
    // std::cout << vec5b << std::endl;
}
