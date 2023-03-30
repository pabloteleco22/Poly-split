#include <gtest/gtest.h>
#include "../lib/poly/vector.hpp"

TEST(PointTest, DefaultVector) {
    Vector vec;
    ASSERT_EQ(vec.x, 0.0);
    ASSERT_EQ(vec.y, 0.0);
    ASSERT_EQ(vec.z, 0.0);
}

TEST(PointTest, CustomVector) {
    double expected_x{1.3};
    double expected_y{3.7};
    double expected_z{9.4};

    Vector vec{expected_x, expected_y, expected_z};

    ASSERT_EQ(vec.x, expected_x);
    ASSERT_EQ(vec.y, expected_y);
    ASSERT_EQ(vec.z, expected_z);
}

TEST(PointTest, Neg) {
    double expected_x{1.3};
    double expected_y{3.7};
    double expected_z{9.4};

    Vector vec{expected_x, expected_y, expected_z};
    Vector neg{-vec};

    ASSERT_EQ(neg.x, -expected_x);
    ASSERT_EQ(neg.y, -expected_y);
    ASSERT_EQ(neg.z, -expected_z);
}

TEST(PointTest, Length) {
    double x{1.3};
    double y{3.7};
    double z{9.4};
    double expected_length{sqrt(x*x + y*y + z*z)};

    Vector vec{x, y, z};

    ASSERT_EQ(vec.length(), expected_length);
}