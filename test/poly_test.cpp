#include <gtest/gtest.h>
#include "../lib/poly/vector.hpp"
#include "../lib/poly/line.hpp"
#include "../lib/poly/polygon.hpp"

/* Vector Tests */
TEST(VectorTest, DefaultVector) {
    const Vector vec;
    ASSERT_EQ(vec.x, 0);
    ASSERT_EQ(vec.y, 0);
}

TEST(VectorTest, CustomVector) {
    const double expected_x{1.3};
    const double expected_y{3.7};

    const Vector vec{expected_x, expected_y};

    ASSERT_EQ(vec.x, expected_x);
    ASSERT_EQ(vec.y, expected_y);
}

TEST(VectorTest, Neg) {
    const double expected_x{1.3};
    const double expected_y{3.7};

    const Vector vec{expected_x, expected_y};
    const Vector neg{-vec};

    ASSERT_EQ(neg.x, -expected_x);
    ASSERT_EQ(neg.y, -expected_y);
}

TEST(VectorTest, Length) {
    const double x{1.3};
    const double y{3.7};
    const double expected_length{sqrt(x*x + y*y)};

    const Vector vec{x, y};

    ASSERT_EQ(vec.length(), expected_length);
}

TEST(VectorTest, Absolute) {
    const double x{-1.3};
    const double y{3.7};
    const double expected_x{-x};
    const double expected_y{y};

    const Vector vec{x, y};
    const Vector expected_vec{expected_x, expected_y};

    ASSERT_EQ(vec.abs(), expected_vec);
}

/* Line Tests */
TEST(LineTest, DefaultLine) {
    const Line lin;
    const Vector expected_point{0, 0};

    ASSERT_EQ(lin.getStart(), expected_point);
    ASSERT_EQ(lin.getEnd(), expected_point);
}

TEST(LineTest, CustomLine) {
    const Vector start_point{5, 8};
    const Vector end_point{8.9, 3};
    const Line lin{start_point, end_point};

    ASSERT_EQ(lin.getStart(), start_point);
    ASSERT_EQ(lin.getEnd(), end_point);
}

TEST(LineTest, reverse) {
    const Vector start_point{5, 8};
    const Vector end_point{8.9, 3};
    const Line lin{start_point, end_point};

    ASSERT_EQ(lin.reverse().getStart(), end_point);
    ASSERT_EQ(lin.reverse().getEnd(), start_point);
}

TEST(LineTest, Length) {
    const Vector start_point{5, 8};
    const Vector end_point{8, 3};
    const Line lin{start_point, end_point};
    const Vector distance_vector{end_point - start_point};

    const double expected_distance{distance_vector.length()};

    ASSERT_EQ(lin.length(), expected_distance);
}

TEST(LineTest, PointAlong) {
    const Vector start_point;
    const Vector end_point{25, 25};
    const Line lin{start_point, end_point};

    const Vector expected_point{8.48528137423857, 8.48528137423857};
    const Vector result = lin.getPointAlong(12);

    ASSERT_EQ(result, expected_point);
}

TEST(LineTest, DistanceIn) {
    const Vector start_point;
    const Vector end_point{10, 10};
    const Vector distance_point{2, 4};
    const Line lin{start_point, end_point};

    const double expected_distance{1.414213562};

    ASSERT_LE(fabs(fabs(lin.getDistance(distance_point)) - expected_distance), POLY_SPLIT_EPS);
}

TEST(LineTest, DistanceOut) {
    const Vector start_point;
    const Vector end_point{10, 10};
    const Vector distance_point{-2, -4};
    const Line lin{start_point, end_point};

    const double expected_distance{1.414213562};

    ASSERT_LE(fabs(fabs(lin.getDistance(distance_point)) - expected_distance), POLY_SPLIT_EPS);
}

TEST(LineTest, LineNearestPointIn) {
    const Vector start_point;
    const Vector end_point{10, 10};
    const Vector distance_point{2, 4};
    const Line lin{start_point, end_point};
    const Vector expected_point{3, 3};

    ASSERT_EQ(lin.getLineNearestPoint(distance_point), expected_point);
}

TEST(LineTest, LineNearestPointOut) {
    const Vector start_point;
    const Vector end_point{10, 10};
    const Vector distance_point{-2, -4};
    const Line lin{start_point, end_point};
    const Vector expected_point{-3, -3};

    ASSERT_EQ(lin.getLineNearestPoint(distance_point), expected_point);
}

TEST(LineTest, SegmentNearestPoint) {
    const Vector start_point;
    const Vector end_point{10, 10};
    const Vector distance_point{2, 4};
    const Line lin{start_point, end_point};
    const Vector expected_point{3, 3};

    ASSERT_EQ(lin.getSegmentNearestPoint(distance_point), expected_point);
}

TEST(LineTest, SegmentNearestPointOut) {
    const Vector start_point;
    const Vector end_point{10, 10};
    const Vector distance_point{-2, -4};
    const Line lin{start_point, end_point};
    const Vector expected_point{0, 0};

    ASSERT_EQ(lin.getSegmentNearestPoint(distance_point), expected_point);
}

TEST(LineTest, PointSideAbove) {
    const Vector start_point;
    const Vector end_point{10, 10};
    const Vector distance_point{2, 4};
    const Line lin{start_point, end_point};
    const int expected_result{1};

    ASSERT_EQ(lin.pointSide(distance_point), expected_result);
}

TEST(LineTest, PointSideBelow) {
    const Vector start_point;
    const Vector end_point{10, 10};
    const Vector distance_point{-2, -4};
    const Line lin{start_point, end_point};
    const int expected_result{-1};

    ASSERT_EQ(lin.pointSide(distance_point), expected_result);
}

TEST(LineTest, PointSideInside) {
    const Vector start_point;
    const Vector end_point{10, 10};
    const Vector distance_point{-1, -1};
    const Line lin{start_point, end_point};
    const int expected_result{0};

    ASSERT_EQ(lin.pointSide(distance_point), expected_result);
}

TEST(LineTest, CrossLineLineTrue) {
    const Vector start_point1;
    const Vector end_point1{4, 4};
    const Vector start_point2{0, 4};
    const Vector end_point2{6, 0};
    Vector inter_point;
    const Vector expected_inter_point{2.4, 2.4};
    const Line lin1{start_point1, end_point1};
    const Line lin2{start_point2, end_point2};

    ASSERT_TRUE(lin1.crossLineLine(lin2, inter_point));
    ASSERT_EQ(inter_point, expected_inter_point);
}

TEST(LineTest, CrossLineLineFalse) {
    const Vector start_point1;
    const Vector end_point1{4, 4};
    const Vector start_point2{0, 4};
    const Vector end_point2{-4, 0};
    Vector inter_point;
    const Line lin1{start_point1, end_point1};
    const Line lin2{start_point2, end_point2};

    ASSERT_FALSE(lin1.crossLineLine(lin2, inter_point));
}

TEST(LineTest, CrossLineSegmentTrue) {
    const Vector line_start_point;
    const Vector line_end_point{4, 4};
    const Vector segment_start_point{0, 4};
    const Vector segment_end_point{6, 0};
    Vector inter_point;
    const Vector expected_inter_point{2.4, 2.4};
    const Line line{line_start_point, line_end_point};
    const Line segment{segment_start_point, segment_end_point};

    ASSERT_TRUE(line.crossLineSegment(segment, inter_point));
    ASSERT_EQ(inter_point, expected_inter_point);
}

TEST(LineTest, CrossLineSegmentFalse) {
    const Vector line_start_point;
    const Vector line_end_point{4, 4};
    const Vector segment_start_point{0, 6};
    const Vector segment_end_point{18, 0};
    Vector inter_point;
    const Line line{line_start_point, line_end_point};
    const Line segment{segment_start_point, segment_end_point};

    ASSERT_FALSE(segment.crossLineSegment(line, inter_point));
}

TEST(LineTest, CrossSegmentSegmentTrue) {
    const Vector start_point1;
    const Vector end_point1{4, 4};
    const Vector start_point2{0, 4};
    const Vector end_point2{6, 0};
    Vector inter_point;
    const Vector expected_inter_point{2.4, 2.4};
    const Line segment1{start_point1, end_point1};
    const Line segment2{start_point2, end_point2};

    ASSERT_TRUE(segment1.crossSegmentSegment(segment2, inter_point));
    ASSERT_EQ(inter_point, expected_inter_point);
}

TEST(LineTest, CrossSegmentSegmentFalse1) {
    const Vector start_point1;
    const Vector end_point1{4, 4};
    const Vector start_point2{0, 6};
    const Vector end_point2{18, 0};
    Vector inter_point;
    const Vector expected_inter_point{2.4, 2.4};
    const Line segment1{start_point1, end_point1};
    const Line segment2{start_point2, end_point2};

    ASSERT_FALSE(segment1.crossSegmentSegment(segment2, inter_point));
}

TEST(LineTest, CrossSegmentSegmentFalse2) {
    const Vector start_point1{0, 6};
    const Vector end_point1{18, 0};
    const Vector start_point2;
    const Vector end_point2{4, 4};
    Vector inter_point;
    const Vector expected_inter_point{2.4, 2.4};
    const Line segment1{start_point1, end_point1};
    const Line segment2{start_point2, end_point2};

    ASSERT_FALSE(segment1.crossSegmentSegment(segment2, inter_point));
}

TEST(LineTest, IsSameTrue) {
    const Vector start_point1;
    const Vector end_point1{2, 4};
    const Vector start_point2;
    const Vector end_point2{4, 8};
    const Line line1{start_point1, end_point1};
    const Line line2{start_point2, end_point2};

    ASSERT_TRUE(Line::is_same(line1, line2));
}

TEST(LineTest, IsSameFalse) {
    const Vector start_point1;
    const Vector end_point1{2, 4};
    const Vector start_point2;
    const Vector end_point2{4, 8.1};
    const Line line1{start_point1, end_point1};
    const Line line2{start_point2, end_point2};

    ASSERT_FALSE(Line::is_same(line1, line2));
}

TEST(LineTest, Bisector1) {
    const Vector start_point1;
    const Vector end_point1{0, 1};
    const Vector start_point2;
    const Vector end_point2{1, 0};
    const Line line1{start_point1, end_point1};
    const Line line2{start_point2, end_point2};

    const Vector expected_start_point;
    const Vector expected_end_point{1, -1};
    const Line expected_bisector{expected_start_point, expected_end_point};

    const Line returned = Line::getBisector(line1, line2);
    Vector inter;

    ASSERT_FALSE(returned.crossLineLine(expected_bisector, inter));
    ASSERT_EQ(returned.getDistance(expected_end_point), 0);
}

TEST(LineTest, Bisector2) {
    const Vector start_point;
    const Vector end_point{0, 1};
    const Line line{start_point, end_point};

    const Vector expected_start_point;
    const Vector expected_end_point{end_point};
    const Line expected_bisector{expected_start_point, expected_end_point};

    const Line returned = Line::getBisector(line, line);
    Vector inter;

    ASSERT_FALSE(returned.crossLineLine(expected_bisector, inter));
    ASSERT_EQ(returned.getDistance(expected_end_point), 0);
}

TEST(LineTest, TanAngleZero) {
    const Vector start_point;
    const Vector end_point{0, 1};
    const Line line{start_point, end_point};

    const double expected_tan{0};

    ASSERT_EQ(Line::getTanAngle(line, line), expected_tan);
}

TEST(LineTest, TanAngle1) {
    const Vector start_point1;
    const Vector end_point1{0, 1};
    const Vector start_point2;
    const Vector end_point2{1, 1};
    const Line line1{start_point1, end_point1};
    const Line line2{start_point2, end_point2};

    const double expected_tan{-1};

    ASSERT_EQ(Line::getTanAngle(line1, line2), expected_tan);
}

TEST(LineTest, DirectedLine) {
    const Vector point{1, 2};
    const Vector vector{1, 1};
    const Line result_line = Line::directedLine(point, vector);
    const Vector expected_start_point{1, 2};
    const Vector expected_end_point{4.5, 5.5};
    const Line expected_line{expected_start_point, expected_end_point};

    ASSERT_TRUE(Line::is_same(result_line, expected_line));
}

/* Polygon Tests */
TEST(PolygonTest, CountSquare) {
    Vectors pol_points;
    pol_points.push_back(Vector{});
    pol_points.push_back(Vector{2, 0});
    pol_points.push_back(Vector{2, 2});
    pol_points.push_back(Vector{0, 2});
    const Polygon pol{pol_points};

    const double expected_sqrt{4};

    ASSERT_EQ(pol.countSquare(), expected_sqrt);
}

TEST(PolygonTest, SplitTrue) {
    Vectors original_points;
    original_points.push_back(Vector{});
    original_points.push_back(Vector{2, 0});
    original_points.push_back(Vector{2, 2});
    original_points.push_back(Vector{0, 2});
    const Polygon original_poly{original_points};
    Polygon first_poly;
    Polygon second_poly;
    Line cut_line;
    const double expected_area{3};

    ASSERT_TRUE(original_poly.split(expected_area, first_poly, second_poly, cut_line));
    ASSERT_EQ(second_poly.countSquare(), expected_area);
    ASSERT_EQ(first_poly.countSquare() + second_poly.countSquare(), original_poly.countSquare());
}

TEST(PolygonTest, SplitFalse) {
    Vectors original_points;
    original_points.push_back(Vector{});
    original_points.push_back(Vector{2, 0});
    original_points.push_back(Vector{2, 2});
    original_points.push_back(Vector{0, 2});
    const Polygon original_poly{original_points};
    Polygon first_poly;
    Polygon second_poly;
    Line cut_line;
    const double expected_area{300};

    ASSERT_FALSE(original_poly.split(expected_area, first_poly, second_poly, cut_line));
}

TEST(PolygonTest, FindDistanceOutside) {
    Vectors points;
    points.push_back(Vector{});
    points.push_back(Vector{2, 0});
    points.push_back(Vector{2, 2});
    points.push_back(Vector{0, 2});
    const Polygon poly{points};

    const Vector point{2, 3};
    const double expected_distance{1};

    ASSERT_EQ(poly.findDistance(point), expected_distance);
}

TEST(PolygonTest, FindDistanceInside) {
    Vectors points;
    points.push_back(Vector{});
    points.push_back(Vector{2, 0});
    points.push_back(Vector{2, 2});
    points.push_back(Vector{0, 2});
    const Polygon poly{points};

    const Vector point{1, 1};
    const double expected_distance{1};

    ASSERT_EQ(poly.findDistance(point), expected_distance);
}

TEST(PolygonTest, FindEmptyDistance) {
    Vectors points;
    const Polygon poly{points};

    const Vector point{2, 3};

    ASSERT_THROW(poly.findDistance(point), Polygon::NotEnoughPointsException);
}

TEST(PolygonTest, FindNearestPointOutside) {
    Vectors points;
    points.push_back(Vector{});
    points.push_back(Vector{2, 0});
    points.push_back(Vector{2, 2});
    points.push_back(Vector{0, 2});
    const Polygon poly{points};

    const Vector point{3, 3};
    const Vector expected_point{2, 2};

    ASSERT_EQ(poly.findNearestPoint(point), expected_point);
}

TEST(PolygonTest, FindNearestPointInside) {
    Vectors points;
    points.push_back(Vector{});
    points.push_back(Vector{2, 0});
    points.push_back(Vector{2, 2});
    points.push_back(Vector{0, 2});
    const Polygon poly{points};

    const Vector point{1, 1.1};
    const Vector expected_point{1, 2};

    ASSERT_EQ(poly.findNearestPoint(point), expected_point);
}

TEST(PolygonTest, FindEmptyNearestPoint) {
    Vectors points;
    const Polygon poly{points};

    const Vector point{3, 3};

    ASSERT_THROW(poly.findNearestPoint(point), Polygon::NotEnoughPointsException);
}

TEST(PolygonTest, FindCenter) {
    Vectors points;
    points.push_back(Vector{});
    points.push_back(Vector{2, 0});
    points.push_back(Vector{2, 2});
    points.push_back(Vector{0, 2});
    const Polygon poly{points};

    const Vector expected_point{1, 1};

    ASSERT_EQ(poly.countCenter(), expected_point);
}

TEST(PolygonTest, FindCenterEmpty) {
    Vectors points;
    const Polygon poly{points};

    const Vector expected_point{};

    ASSERT_THROW(poly.countCenter(), Polygon::NotEnoughPointsException);
}

TEST(PolygonTest, SplitNearestEdge) {
    Vectors points;
    points.push_back(Vector{});
    points.push_back(Vector{2, 0});
    points.push_back(Vector{2, 2});
    points.push_back(Vector{0, 2});
    Polygon poly{points};

    const Vector split_point{4, 1};
    const Vector expected_point{2, 1};
    const size_t expected_size{5};

    poly.splitNearestEdge(split_point);

    ASSERT_EQ(poly[2], expected_point);
    ASSERT_EQ(poly.size(), expected_size);
}

TEST(PolygonTest, SplitNearestEdgeCorner) {
    Vectors points;
    points.push_back(Vector{});
    points.push_back(Vector{2, 0});
    points.push_back(Vector{2, 2});
    points.push_back(Vector{0, 2});
    Polygon poly{points};

    const Vector split_point{4, 4};
    const size_t expected_size{4};

    poly.splitNearestEdge(split_point);

    ASSERT_EQ(poly.size(), expected_size);
}

TEST(PolygonTest, IsPointInsideTrue) {
    Vectors pol_points;
    pol_points.push_back(Vector{});
    pol_points.push_back(Vector{2, 0});
    pol_points.push_back(Vector{2, 2});
    pol_points.push_back(Vector{0, 2});
    const Polygon pol{pol_points};

    const Vector point{1, 1};

    ASSERT_TRUE(pol.isPointInside(point));
}

TEST(PolygonTest, IsPointInsideFalse) {
    Vectors pol_points;
    pol_points.push_back(Vector{});
    pol_points.push_back(Vector{2, 0});
    pol_points.push_back(Vector{2, 2});
    pol_points.push_back(Vector{0, 2});
    const Polygon pol{pol_points};

    const Vector point{-1, 1};

    ASSERT_FALSE(pol.isPointInside(point));
}

TEST(PolygonTest, IsPointInsideException) {
    Vectors pol_points;
    const Polygon pol{pol_points};

    const Vector point{-1, 1};

    ASSERT_THROW(pol.isPointInside(point), Polygon::NotEnoughPointsException);
}

TEST(PolygonTest, IsClockWiseTrue) {
    Vectors pol_points;
    pol_points.push_back(Vector{});
    pol_points.push_back(Vector{2, 0});
    pol_points.push_back(Vector{2, 2});
    pol_points.push_back(Vector{0, 2});
    const Polygon pol{pol_points};

    ASSERT_TRUE(pol.isClockwise());
}

TEST(PolygonTest, IsClockWiseFalse) {
    Vectors pol_points;
    pol_points.push_back(Vector{0, 2});
    pol_points.push_back(Vector{2, 2});
    pol_points.push_back(Vector{2, 0});
    pol_points.push_back(Vector{});
    const Polygon pol{pol_points};

    ASSERT_FALSE(pol.isClockwise());
}

TEST(PolygonTest, IsClockWiseException) {
    Vectors pol_points;
    const Polygon pol{pol_points};

    ASSERT_THROW(pol.isClockwise(), Polygon::NotEnoughPointsException);
}