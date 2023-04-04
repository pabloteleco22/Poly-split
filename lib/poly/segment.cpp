#include "line.hpp"

Segment::Segment() {
}

Segment::Segment(const Line &l) {
    this->l = l;
}

Segment::Segment(const Point &start, const Point &end) {
    l = Line{start, end};
}

Segment::Segment(double a, double b, double c) {
    l = Line{a, b, c};
}

/**
 * @brief It returns the start point of the segment
*/
Point Segment::get_start() const {
    return l.get_p1();
}

/**
 * @brief It returns the end point of the segment
*/
Point Segment::get_end() const {
    return l.get_p2();
}

/**
 * @brief It returns the length of the segment
*/
double Segment::length() const {
    return l.get_p1().distance(l.get_p2());
}

/**
 * @brief It returns the square of the length of the segment
*/
double Segment::square_length() const {
    return l.get_p1().square_distance(l.get_p2());
}

/**
 * @brief It returns the same segment but the start point is
 * the new end point and vice versa
*/
Segment Segment::reverse() const {
    return Segment{l.reverse()};
}

inline bool inside(double v, double min, double max) {
    return ((min <= (v + POLY_SPLIT_EPS)) and (v <= (max + POLY_SPLIT_EPS)));
}

inline double det(double a, double b, double c, double d) {
    return (((a) * (d)) - ((b) * (c)));
}

inline double minimum(double a, double b) {
    return (((a) > (b)) ? (b) : (a));
}

inline double maximum(double a, double b) {
    return (((a) < (b)) ? (b) : (a));
}

/**
 * @brief Returns a point on the line one distance t away from
 * the start point
*/
Point Segment::get_point_along(double t) const {
    Point p{l.get_point_along(t)};
    Point start{l.get_p1()};
    Point end{l.get_p2()};
    Point min{minimum(start.x, end.x), minimum(start.y, end.y)};
    Point max{maximum(start.x, end.x), maximum(start.y, end.y)};
    
    if (!inside(p.x, min.x, max.x) or (!inside(p.y, min.y, max.y))) {
        p = get_nearest_point(p);
    }

    return p;
}

/**
 * @brief Returns the distance between the point and the line
*/
double Segment::get_distance(const Point &point) const {
    return l.get_distance(point);
}

/**
 * @brief Returns the nearest point from the segment,
 * which means that it takes into account the start
 * and end points
*/
Point Segment::get_nearest_point(const Point &point) const {
    Vector dir{l.b, -l.a};
    double u{Vector{point - l.p1}.dot(dir) / dir.square_length()};
    if (u < 0)
        return l.p1;
    else if (u > 1)
        return l.p2;
    else
        return l.p1 + dir * u;
}

/**
 * @brief Returns if the point is over, under or in the line
 * 
 * @returns
 *  1 if above,
 *  0 if in,
 *  -1 if below
*/
PointSide Segment::point_side(const Point &point) const {

}

/**
 * @brief Returns whether the line and the segment intersect and
 * the point of intersection between them
 * 
 * @param 
 * line: The line, not the segment.
 *
 * @param
 * result: The intersection point.
 * 
 * @return If the line and the segment intersect
*/
bool Segment::cross_line_segment(const Segment &line, Point &result) const {

}

/**
 * @brief Returns whether the thw segments intersect and
 * the point of intersection between them
 * 
 * @param
 * result: The intersection point.
 * 
 * @return If the line and the segment intersect
*/
bool Segment::cross_segment_segment(const Segment &line, Point &result) const {

}

/**
 * @brief Returns whether the two lines intersect and
 * the point of intersection between them
 * 
 * @param
 * result: The intersection point.
 * 
 * @return If the line and the segment intersect
*/
bool Segment::cross_line_line(const Segment &line, Point &result) const {

}

bool Segment::operator==(const Segment &other) const {

}

/**
 * @brief Returns true if l1 and l2 are the same line
*/
bool Segment::is_same(const Segment &l1, const Segment &l2) {

}

/**
 * @brief Returns the bisector between the two lines
*/
Segment Segment::get_bisector(const Segment &l1, const Segment &l2) {

}

/**
 * @brief Returns the tangent of the angle between the two lines in radians
*/
double Segment::get_tan_angle(const Segment &l1, const Segment &l2) {

}

/**
 * @brief Returns a line from a point and a vector
 * 
 * @param
 * p: Point
 * @param
 * d: Vector
*/
Segment Segment::directed_line(const Point &p, const Vector &v) {

}