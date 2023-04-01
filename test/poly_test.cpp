#include <gtest/gtest.h>
#include "../lib/poly/vector.hpp"
#include "../lib/poly/line.hpp"

TEST(VectorTest, DefaultVector) {
    Vector vec;
    ASSERT_EQ(vec.x, 0.0);
    ASSERT_EQ(vec.y, 0.0);
    ASSERT_EQ(vec.z, 0.0);
}

TEST(VectorTest, CustomVector) {
    double expected_x{1.3};
    double expected_y{3.7};
    double expected_z{9.4};

    Vector vec{expected_x, expected_y, expected_z};

    ASSERT_EQ(vec.x, expected_x);
    ASSERT_EQ(vec.y, expected_y);
    ASSERT_EQ(vec.z, expected_z);
}

TEST(VectorTest, Neg) {
    double expected_x{1.3};
    double expected_y{3.7};
    double expected_z{9.4};

    Vector vec{expected_x, expected_y, expected_z};
    Vector neg{-vec};

    ASSERT_EQ(neg.x, -expected_x);
    ASSERT_EQ(neg.y, -expected_y);
    ASSERT_EQ(neg.z, -expected_z);
}

TEST(VectorTest, Length) {
    double x{1.3};
    double y{3.7};
    double z{9.4};
    double expected_length{sqrt(x*x + y*y + z*z)};

    Vector vec{x, y, z};

    ASSERT_EQ(vec.length(), expected_length);
}

TEST(VectorTest, Absolute) {
    double x{-1.3};
    double y{-3.7};
    double z{9.4};
    double expected_x{-x};
    double expected_y{-y};
    double expected_z{z};

    Vector vec{x, y, z};
    Vector expected_vec{expected_x, expected_y, expected_z};

    ASSERT_EQ(vec.abs(), expected_vec);
}

TEST(LineTest, DefaultLine) {
    Line lin;
    Vector expected_point{0.0, 0.0, 0.0};

    ASSERT_EQ(lin.getStart(), expected_point);
    ASSERT_EQ(lin.getEnd(), expected_point);
}

TEST(LineTest, CustomLine) {
    Vector start_point{5.0, 8.0, 2.0};
    Vector end_point{8.9, 3.0, 9.0};
    Line lin{start_point, end_point};

    ASSERT_EQ(lin.getStart(), start_point);
    ASSERT_EQ(lin.getEnd(), end_point);
}

TEST(LineTest, reverse) {
    Vector start_point{5.0, 8.0, 2.0};
    Vector end_point{8.9, 3.0, 9.0};
    Line lin{start_point, end_point};

    ASSERT_EQ(lin.reverse().getStart(), end_point);
    ASSERT_EQ(lin.reverse().getEnd(), start_point);
}

TEST(LineTest, Length) {
    Vector start_point{5.0, 8.0, 2.0};
    Vector end_point{8.0, 3.0, 9.0};
    Line lin{start_point, end_point};
    Vector distance_vector{end_point - start_point};

    double expected_distance{distance_vector.length()};

    ASSERT_EQ(lin.length(), expected_distance);
}

TEST(LineTest, PointAlong) {
    Vector start_point;
    Vector end_point{25.0, 25.0, 25.0};
    Line lin{start_point, end_point};

    Vector expected_point{24.0, 24.0, 24.0};
    Vector result = lin.getPointAlong(41.56921938);

    ASSERT_LT((result - expected_point).abs().x, POLY_SPLIT_EPS);
    ASSERT_LT((result - expected_point).abs().y, POLY_SPLIT_EPS);
    ASSERT_LT((result - expected_point).abs().z, POLY_SPLIT_EPS);
}

TEST(LineTest, Distance) {
    Vector start_point;
    Vector end_point{10.0, 10.0, 0.0};
    Vector distance_point{2.0, 4.0, 0.0};
    Line lin{start_point, end_point};

    double expected_distance{1};

    ASSERT_EQ(lin.getDistance(distance_point), expected_distance);
}