#include "line.hpp"

#include <cassert>

Line::Line() {}

Line::Line(const Vector &start, const Vector &end) : start(start), end(end) {
    a = start.y - end.y;
    b = end.x - start.x;
    c = start.x * end.y - end.x * start.y;
}

Line::Line(double a, double b, double c) : a{a}, b{b}, c{c} {
    if (fabs(a) <= POLY_SPLIT_EPS && fabs(b) >= POLY_SPLIT_EPS) {
        start.x = -1000;
        start.y = -(c / b);

        end.x = 1000;
        end.y = start.y;
    } else if (fabs(b) <= POLY_SPLIT_EPS && fabs(a) >= POLY_SPLIT_EPS) {
        start.x = -(c / a);
        start.y = -1000;

        end.x = start.x;
        end.y = 1000;
    } else {
        start.x = -1000;
        start.y = -((a * start.x + c) / b);

        end.x = 1000;
        end.y = -((a * end.x + c) / b);
    }
}

double Line::getDistance(const Vector &point) const {
    double n{a * point.x + b * point.y + c};
    double m{sqrt(a * a + b * b)};
    assert(m != 0);
    return n / m;
}

Vector Line::getLineNearestPoint(const Vector &point) const {
    Vector dir{b, -a};
    double u{(point - start).dot(dir) / dir.squareLength()};
    return start + dir * u;
}

Vector Line::getSegmentNearestPoint(const Vector &point) const {
    Vector dir{b, -a};
    double u{(point - start).dot(dir) / dir.squareLength()};
    if (u < 0)
        return start;
    else if (u > 1)
        return end;
    else
        return start + dir * u;
}

int Line::pointSide(const Vector &point) const {
    double s{a * (point.x - start.x) + b * (point.y - start.y)};
    return (s > 0 ? 1 : (s < 0 ? -1 : 0));
}

#define inside(v, min, max) (((min) <= (v) + (POLY_SPLIT_EPS)) && ((v) <= (max) + (POLY_SPLIT_EPS)))
#define det(a, b, c, d) (((a) * (d)) - ((b) * (c)))
#define minimum(a, b) (((a) > (b)) ? (b) : (a))
#define maximum(a, b) (((a) < (b)) ? (b) : (a))

bool Line::crossLineSegment(const Line &line, Vector &result) const {
    double d{det(a, b, line.a, line.b)};
    if (d == 0)
        return false;

    result.x = -det(c, b, line.c, line.b) / d;
    result.y = -det(a, c, line.a, line.c) / d;

    return inside(result.x, minimum(line.start.x, line.end.x), maximum(line.start.x, line.end.x)) &&
            inside(result.y, minimum(line.start.y, line.end.y), maximum(line.start.y, line.end.y));
}

bool Line::crossSegmentSegment(const Line &line, Vector &result) const {
    double d{det(a, b, line.a, line.b)};
    if (d == 0)
        return false;

    result.x = -det(c, b, line.c, line.b) / d;
    result.y = -det(a, c, line.a, line.c) / d;

    return inside(result.x, minimum(start.x, end.x), maximum(start.x, end.x)) &&
           inside(result.y, minimum(start.y, end.y), maximum(start.y, end.y)) &&
           inside(result.x, minimum(line.start.x, line.end.x), maximum(line.start.x, line.end.x)) &&
           inside(result.y, minimum(line.start.y, line.end.y), maximum(line.start.y, line.end.y));
}

bool Line::crossLineLine(const Line &line, Vector &result) const {
    double d{det(a, b, line.a, line.b)};
    if (d == 0)
        return false;

    result.x = -det(c, b, line.c, line.b) / d;
    result.y = -det(a, c, line.a, line.c) / d;

    return true;
}

bool Line::operator==(const Line &other) const {
    return (pointSide(other.start) == 0) and (pointSide(other.end) == 0);
}

bool Line::is_same(const Line &l1, const Line &l2) {
    return l1 == l2;
}

Line Line::getBisector(const Line &l1, const Line &l2) {
    if (l1 == l2) {
        return Line{l1};
    } else {
        double q1{sqrt(l1.a * l1.a + l1.b * l1.b)};
        double q2{sqrt(l2.a * l2.a + l2.b * l2.b)};

        double a{l1.a / q1 - l2.a / q2};
        double b{l1.b / q1 - l2.b / q2};
        double c{l1.c / q1 - l2.c / q2};

        return Line{a, b, c};
    }
}

double Line::getTanAngle(const Line &l1, const Line &l2) {
    return (l1.a * l2.b - l2.a * l1.b) / (l1.a * l2.a + l1.b * l2.b);
}

Vector Line::getStart() const {
    return start;
}

Vector Line::getEnd() const {
    return end;
}

double Line::length() const {
    double x{end.x - start.x};
    double y{end.y - start.y};

    return sqrt(x * x + y * y);
}

double Line::squareLength() const {
    double x{end.x - start.x};
    double y{end.y - start.y};

    return x * x + y * y;
}

Line Line::reverse() const {
    return Line{end, start};
}

Vector Line::getPointAlong(double t) const {
    return start + (end - start).norm() * t;
}

Line Line::directedLine(const Vector &p, const Vector &d) {
    return Line{p, p + d};
}
