#include <gtest/gtest.h>
#include "../lib/poly/vector.hpp"
#include "../lib/poly/line.hpp"
#include <iostream>

using namespace std;

TEST(VectorTest, DefaultVector) {
    Vector vec;
    ASSERT_EQ(vec.x, 0.0);
    ASSERT_EQ(vec.y, 0.0);
}

TEST(VectorTest, CustomVector) {
    double expected_x{1.3};
    double expected_y{3.7};

    Vector vec{expected_x, expected_y};

    ASSERT_EQ(vec.x, expected_x);
    ASSERT_EQ(vec.y, expected_y);
}

TEST(VectorTest, Neg) {
    double expected_x{1.3};
    double expected_y{3.7};

    Vector vec{expected_x, expected_y};
    Vector neg{-vec};

    ASSERT_EQ(neg.x, -expected_x);
    ASSERT_EQ(neg.y, -expected_y);
}

TEST(VectorTest, Length) {
    double x{1.3};
    double y{3.7};
    double expected_length{sqrt(x*x + y*y)};

    Vector vec{x, y};

    ASSERT_EQ(vec.length(), expected_length);
}

TEST(VectorTest, Absolute) {
    double x{-1.3};
    double y{3.7};
    double expected_x{-x};
    double expected_y{y};

    Vector vec{x, y};
    Vector expected_vec{expected_x, expected_y};

    ASSERT_EQ(vec.abs(), expected_vec);
}

TEST(LineTest, DefaultLine) {
    Line lin;
    Vector expected_point{0.0, 0.0};

    ASSERT_EQ(lin.getStart(), expected_point);
    ASSERT_EQ(lin.getEnd(), expected_point);
}

TEST(LineTest, CustomLine) {
    Vector start_point{5.0, 8.0};
    Vector end_point{8.9, 3.0};
    Line lin{start_point, end_point};

    ASSERT_EQ(lin.getStart(), start_point);
    ASSERT_EQ(lin.getEnd(), end_point);
}

TEST(LineTest, reverse) {
    Vector start_point{5.0, 8.0};
    Vector end_point{8.9, 3.0};
    Line lin{start_point, end_point};

    ASSERT_EQ(lin.reverse().getStart(), end_point);
    ASSERT_EQ(lin.reverse().getEnd(), start_point);
}

TEST(LineTest, Length) {
    Vector start_point{5.0, 8.0};
    Vector end_point{8.0, 3.0};
    Line lin{start_point, end_point};
    Vector distance_vector{end_point - start_point};

    double expected_distance{distance_vector.length()};

    ASSERT_EQ(lin.length(), expected_distance);
}

TEST(LineTest, PointAlong) {
    Vector start_point;
    Vector end_point{25.0, 25.0};
    Line lin{start_point, end_point};

    Vector expected_point{8.48528137423857, 8.48528137423857};
    Vector result = lin.getPointAlong(12.0);

    ASSERT_EQ(result, expected_point);
}

TEST(LineTest, DistanceIn) {
    Vector start_point;
    Vector end_point{10.0, 10.0};
    Vector distance_point{2.0, 4.0};
    Line lin{start_point, end_point};

    double expected_distance{1.414213562};

    ASSERT_LE(fabs(fabs(lin.getDistance(distance_point)) - expected_distance), POLY_SPLIT_EPS);
}

TEST(LineTest, DistanceOut) {
    Vector start_point;
    Vector end_point{10.0, 10.0};
    Vector distance_point{-2.0, -4.0};
    Line lin{start_point, end_point};

    double expected_distance{1.414213562};

    cout << lin.getDistance(distance_point) << endl;

    ASSERT_LE(fabs(fabs(lin.getDistance(distance_point)) - expected_distance), POLY_SPLIT_EPS);
}

TEST(LineTest, LineNearestPointIn) {
    Vector start_point;
    Vector end_point{10.0, 10.0};
    Vector distance_point{2.0, 4.0};
    Line lin{start_point, end_point};
    Vector expected_point{3.0, 3.0};

    ASSERT_EQ(lin.getLineNearestPoint(distance_point), expected_point);
}

TEST(LineTest, LineNearestPointOut) {
    Vector start_point;
    Vector end_point{10.0, 10.0};
    Vector distance_point{-2.0, -4.0};
    Line lin{start_point, end_point};
    Vector expected_point{-3.0, -3.0};

    ASSERT_EQ(lin.getLineNearestPoint(distance_point), expected_point);
}

TEST(LineTest, SegmentNearestPoint) {
    Vector start_point;
    Vector end_point{10.0, 10.0};
    Vector distance_point{2.0, 4.0};
    Line lin{start_point, end_point};
    Vector expected_point{3.0, 3.0};

    ASSERT_EQ(lin.getSegmentNearestPoint(distance_point), expected_point);
}

TEST(LineTest, SegmentNearestPointOut) {
    Vector start_point;
    Vector end_point{10.0, 10.0};
    Vector distance_point{-2.0, -4.0};
    Line lin{start_point, end_point};
    Vector expected_point{0.0, 0.0};

    ASSERT_EQ(lin.getSegmentNearestPoint(distance_point), expected_point);
}