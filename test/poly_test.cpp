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

TEST(LineTest, PointSideAbove) {
    Vector start_point;
    Vector end_point{10.0, 10.0};
    Vector distance_point{2.0, 4.0};
    Line lin{start_point, end_point};
    int expected_result{1};

    ASSERT_EQ(lin.pointSide(distance_point), expected_result);
}

TEST(LineTest, PointSideBelow) {
    Vector start_point;
    Vector end_point{10.0, 10.0};
    Vector distance_point{-2.0, -4.0};
    Line lin{start_point, end_point};
    int expected_result{-1};

    ASSERT_EQ(lin.pointSide(distance_point), expected_result);
}

TEST(LineTest, PointSideInside) {
    Vector start_point;
    Vector end_point{10.0, 10.0};
    Vector distance_point{-1.0, -1.0};
    Line lin{start_point, end_point};
    int expected_result{0};

    ASSERT_EQ(lin.pointSide(distance_point), expected_result);
}

TEST(LineTest, CrossLineLineTrue) {
    Vector start_point1;
    Vector end_point1{4.0, 4.0};
    Vector start_point2{0.0, 4.0};
    Vector end_point2{6.0, 0.0};
    Vector inter_point;
    Vector expected_inter_point{2.4, 2.4};
    Line lin1{start_point1, end_point1};
    Line lin2{start_point2, end_point2};

    ASSERT_TRUE(lin1.crossLineLine(lin2, inter_point));
    ASSERT_EQ(inter_point, expected_inter_point);
}

TEST(LineTest, CrossLineLineFalse) {
    Vector start_point1;
    Vector end_point1{4.0, 4.0};
    Vector start_point2{0.0, 4.0};
    Vector end_point2{-4.0, 0.0};
    Vector inter_point;
    Line lin1{start_point1, end_point1};
    Line lin2{start_point2, end_point2};

    ASSERT_FALSE(lin1.crossLineLine(lin2, inter_point));
}

TEST(LineTest, CrossLineSegmentTrue) {
    Vector line_start_point;
    Vector line_end_point{4.0, 4.0};
    Vector segment_start_point{0.0, 4.0};
    Vector segment_end_point{6.0, 0.0};
    Vector inter_point;
    Vector expected_inter_point{2.4, 2.4};
    Line line{line_start_point, line_end_point};
    Line segment{segment_start_point, segment_end_point};

    ASSERT_TRUE(line.crossLineSegment(segment, inter_point));
    ASSERT_EQ(inter_point, expected_inter_point);
}

TEST(LineTest, CrossLineSegmentFalse) {
    Vector line_start_point;
    Vector line_end_point{4.0, 4.0};
    Vector segment_start_point{0.0, 6.0};
    Vector segment_end_point{18.0, 0.0};
    Vector inter_point;
    Line line{line_start_point, line_end_point};
    Line segment{segment_start_point, segment_end_point};

    ASSERT_FALSE(segment.crossLineSegment(line, inter_point));
}

TEST(LineTest, CrossSegmentSegmentTrue) {
    Vector start_point1;
    Vector end_point1{4.0, 4.0};
    Vector start_point2{0.0, 4.0};
    Vector end_point2{6.0, 0.0};
    Vector inter_point;
    Vector expected_inter_point{2.4, 2.4};
    Line segment1{start_point1, end_point1};
    Line segment2{start_point2, end_point2};

    ASSERT_TRUE(segment1.crossSegmentSegment(segment2, inter_point));
    ASSERT_EQ(inter_point, expected_inter_point);
}

TEST(LineTest, CrossSegmentSegmentFalse1) {
    Vector start_point1;
    Vector end_point1{4.0, 4.0};
    Vector start_point2{0.0, 6.0};
    Vector end_point2{18.0, 0.0};
    Vector inter_point;
    Vector expected_inter_point{2.4, 2.4};
    Line segment1{start_point1, end_point1};
    Line segment2{start_point2, end_point2};

    ASSERT_FALSE(segment1.crossSegmentSegment(segment2, inter_point));
}

TEST(LineTest, CrossSegmentSegmentFalse2) {
    Vector start_point1{0.0, 6.0};
    Vector end_point1{18.0, 0.0};
    Vector start_point2;
    Vector end_point2{4.0, 4.0};
    Vector inter_point;
    Vector expected_inter_point{2.4, 2.4};
    Line segment1{start_point1, end_point1};
    Line segment2{start_point2, end_point2};

    ASSERT_FALSE(segment1.crossSegmentSegment(segment2, inter_point));
}

TEST(LineTest, IsSameTrue) {
    Vector start_point1;
    Vector end_point1{2.0, 4.0};
    Vector start_point2;
    Vector end_point2{4.0, 8.0};
    Line line1{start_point1, end_point1};
    Line line2{start_point2, end_point2};

    ASSERT_TRUE(Line::is_same(line1, line2));
}

TEST(LineTest, IsSameFalse) {
    Vector start_point1;
    Vector end_point1{2.0, 4.0};
    Vector start_point2;
    Vector end_point2{4.0, 8.1};
    Line line1{start_point1, end_point1};
    Line line2{start_point2, end_point2};

    ASSERT_FALSE(Line::is_same(line1, line2));
}

TEST(LineTest, Bisector1) {
    Vector start_point1;
    Vector end_point1{0.0, 1.0};
    Vector start_point2;
    Vector end_point2{1.0, 0.0};
    Line line1{start_point1, end_point1};
    Line line2{start_point2, end_point2};

    Vector expected_start_point;
    Vector expected_end_point{1.0, -1.0};
    Line expected_bisector{expected_start_point, expected_end_point};

    Line returned = Line::getBisector(line1, line2);
    Vector inter;

    ASSERT_FALSE(returned.crossLineLine(expected_bisector, inter));
    ASSERT_EQ(returned.getDistance(expected_end_point), 0.0);
}

TEST(LineTest, Bisector2) {
    Vector start_point;
    Vector end_point{0.0, 1.0};
    Line line{start_point, end_point};

    Vector expected_start_point;
    Vector expected_end_point{end_point};
    Line expected_bisector{expected_start_point, expected_end_point};

    Line returned = Line::getBisector(line, line);
    Vector inter;

    ASSERT_FALSE(returned.crossLineLine(expected_bisector, inter));
    ASSERT_EQ(returned.getDistance(expected_end_point), 0.0);
}

TEST(LineTest, TanAngleZero) {
    Vector start_point;
    Vector end_point{0.0, 1.0};
    Line line{start_point, end_point};

    const double expected_tan{0};

    ASSERT_EQ(Line::getTanAngle(line, line), expected_tan);
}

TEST(LineTest, TanAngle1) {
    Vector start_point1;
    Vector end_point1{0.0, 1.0};
    Vector start_point2;
    Vector end_point2{1.0, 1.0};
    Line line1{start_point1, end_point1};
    Line line2{start_point2, end_point2};

    const double expected_tan{-1.0};

    ASSERT_EQ(Line::getTanAngle(line1, line2), expected_tan);
}

// TODO: Falta test para directedLine