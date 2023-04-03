#include "polygon.hpp"

#include <cfloat>
#include <algorithm>
#include <exception>

Polygons::Polygons(const Line &l1, const Line &l2) {
    bisector = Line::get_bisector(l1, l2);

    Vector v1{l1.get_start()};
    Vector v2{l1.get_end()};
    Vector v3{l2.get_start()};
    Vector v4{l2.get_end()};

    p1_exist = false;
    p4_exist = false;
    if (v1 != v4) {
        Line l1s{v1, bisector.get_line_nearest_point(v1)};
        Vector p1;
        p1_exist = l1s.cross_line_segment(l2, p1) && p1 != v4;
        if (p1_exist) {
            leftTriangle.push_back(v1);
            leftTriangle.push_back(v4);
            leftTriangle.push_back(p1);

            trapezoid.push_back(p1);
        } else {
            trapezoid.push_back(v4);
        }

        Line l2e{v4, bisector.get_line_nearest_point(v4)};
        Vector p4;
        p4_exist = l2e.cross_line_segment(l1, p4) && p4 != v1;
        if (p4_exist) {
            leftTriangle.push_back(v4);
            leftTriangle.push_back(v1);
            leftTriangle.push_back(p4);

            trapezoid.push_back(p4);
        } else {
            trapezoid.push_back(v1);
        }
    } else {
        trapezoid.push_back(v4);
        trapezoid.push_back(v1);
    }

    p2_exist = false;
    p3_exist = false;
    if (v2 != v3) {
        Line l2s{v3, bisector.get_line_nearest_point(v3)};
        Vector p3;
        p3_exist = l2s.cross_line_segment(l1, p3) && p3 != v2;
        if (p3_exist) {
            rightTriangle.push_back(v3);
            rightTriangle.push_back(v2);
            rightTriangle.push_back(p3);

            trapezoid.push_back(p3);
        } else {
            trapezoid.push_back(v2);
        }

        Line l1e{v2, bisector.get_line_nearest_point(v2)};
        Vector p2;
        p2_exist = l1e.cross_line_segment(l2, p2) && p2 != v3;
        if (p2_exist) {
            rightTriangle.push_back(v2);
            rightTriangle.push_back(v3);
            rightTriangle.push_back(p2);

            trapezoid.push_back(p2);
        } else {
            trapezoid.push_back(v3);
        }
    } else {
        trapezoid.push_back(v2);
        trapezoid.push_back(v3);
    }

    leftTriangleSquare = leftTriangle.count_square();
    trapezoidSquare = trapezoid.count_square();
    rightTriangleSquare = rightTriangle.count_square();

    totalSquare = leftTriangleSquare + trapezoidSquare + rightTriangleSquare;
}

bool Polygons::find_cut_line(double square, Line &cut_line) {
    if (square > totalSquare) {
        return false;
    }

    if (!leftTriangle.empty() && square < leftTriangleSquare) {
        double m{square / leftTriangleSquare};
        Vector p{leftTriangle[1] + (leftTriangle[2] - leftTriangle[1]) * m};
        if (p1_exist) {
            cut_line = Line{p, leftTriangle[0]};
            return true;
        } else if(p4_exist) {
            cut_line = Line{leftTriangle[0], p};
            return true;
        }
    } else if(leftTriangleSquare < square && square < (leftTriangleSquare + trapezoidSquare)) {
        Line t{trapezoid[0], trapezoid[3]};
        double tgA{Line::get_tan_angle(t, bisector)};
        double S{square - leftTriangleSquare};
        double m;
        if (fabs(tgA) > POLY_SPLIT_EPS) {
            double a{Line(trapezoid[0], trapezoid[1]).length()};
            double b{Line(trapezoid[2], trapezoid[3]).length()};
            double hh{2.0 * trapezoidSquare / (a + b)};
            double d{a * a - 4.0 * tgA * S};
            double h{-(-a + sqrt(d)) / (2.0 * tgA)};
            m = h / hh;
        } else {
            m = S / trapezoidSquare;
        }
        Vector p{trapezoid[0] + (trapezoid[3] - trapezoid[0]) * m};
        Vector pp{trapezoid[1] + (trapezoid[2] - trapezoid[1]) * m};

        cut_line = Line{p, pp};
        return true;
    } else if(!rightTriangle.empty() && square > leftTriangleSquare + trapezoidSquare) {
        double S{square - leftTriangleSquare - trapezoidSquare};
        double m{S / rightTriangleSquare};
        Vector p{rightTriangle[2] + (rightTriangle[1] - rightTriangle[2]) * m};
        if (p3_exist) {
            cut_line = Line{rightTriangle[0], p};
            return true;
        } else if (p2_exist) {
            cut_line = Line{p, rightTriangle[0]};
            return true;
        }
    }

    return false;
}

Polygon::NotEnoughPointsException::NotEnoughPointsException() {}

Polygon::NotEnoughPointsException::NotEnoughPointsException(const std::string &message) {
    this->message = std::string{message};
}

Polygon::NotEnoughPointsException::NotEnoughPointsException(const char *message) {
    this->message = std::string{message};
}

const char *Polygon::NotEnoughPointsException::what() const noexcept {
    return message.c_str();
}


Polygon::Polygon() {}

Polygon::Polygon(const Vectors &v) {
    vertex = v;
}

double Polygon::count_square_signed(void) const {
    size_t pointsCount{vertex.size()};
    if (pointsCount < 3) {
        return 0;
    }

    double result{0};
    for (size_t i = 0; i < pointsCount; i++) {
        if (i == 0)
            result += vertex[i].x * (vertex[pointsCount - 1].y - vertex[i + 1].y);
        else if (i == pointsCount - 1)
            result += vertex[i].x * (vertex[i - 1].y - vertex[0].y);
        else
            result += vertex[i].x * (vertex[i - 1].y - vertex[i + 1].y);
    }

    return result / 2.0;
}

double Polygon::count_square() const {
    return fabs(count_square_signed());
}

bool Polygon::split(double square, Polygon &poly1, Polygon &poly2, Line &cutLine) const {
    int polygonSize{static_cast<int>(vertex.size())};

    Vectors polygon{vertex};
    if (!is_clockwise()) {
        std::reverse(polygon.begin(), polygon.end());
    }

    poly1.clear();
    poly2.clear();

    if (count_square() - square <= POLY_SPLIT_EPS) {
        poly1 = *this;
        return false;
    }

    bool minCutLine_exists{false};
    double minSqLength = DBL_MAX;

    for (int i = 0; i < polygonSize - 1; i++) {
        for (int j = i + 1; j < polygonSize; j++) {
            Polygon p1;
            Polygon p2;

            p1.clear();
            p2.clear();
            
            int pc1{j - i};
            for (int z = 1; z <= pc1; ++z) {
                p1.push_back(polygon[z + i]);
            }

            int pc2{polygonSize - pc1};
            for (int z = 1; z <= pc2; ++z) {
                p2.push_back(polygon[(z + j) % polygonSize]);
            }

            Line l1{polygon[i], polygon[i + 1]};
            Line l2{polygon[j], polygon[(j + 1) < polygonSize ? (j + 1) : 0]};
            Line cut;

            if (get_cut(l1, l2, square, p1, p2, cut)) {
                double sqLength{cut.square_length()};
                if (sqLength < minSqLength && is_segment_inside(cut, i, j)) {
                    minSqLength = sqLength;
                    poly1 = p1;
                    poly2 = p2;
                    cutLine = cut;
                    minCutLine_exists = true;
                }
            }
        }
    }

    if (minCutLine_exists) {
        poly1.push_back(cutLine.get_start());
        poly1.push_back(cutLine.get_end());

        poly2.push_back(cutLine.get_end());
        poly2.push_back(cutLine.get_start());

        return true;
    } else {
        poly1 = Polygon{polygon};
        return false;
    }
}

double Polygon::find_distance(const Vector &point) const {
    double distance{std::numeric_limits<double>::infinity()};
    int poly_size{static_cast<int>(vertex.size())};
    if (poly_size < 2)
        throw Polygon::NotEnoughPointsException{"The polygon has not enough vertices"};

    for (int i = 0; i < poly_size - 1; i++) {
        Line line{vertex[i], vertex[i + 1]};
        Vector p{line.get_segment_nearest_point(point)};
        double l{(p - point).length()};
        if (l < distance)
            distance = l;
    }
    
    Line line{vertex[poly_size - 1], vertex[0]};
    Vector p{line.get_segment_nearest_point(point)};
    double l{(p - point).length()};
    if (l < distance)
        distance = l;

    return distance;
}

Vector Polygon::find_nearest_point(const Vector &point) const {
    Vector result;
    double distance{std::numeric_limits<double>::infinity()};
    int poly_size{static_cast<int>(vertex.size())};
    if (poly_size < 2)
        throw Polygon::NotEnoughPointsException{"The polygon has not enough vertices"};

    for (int i = 0; i < poly_size - 1; i++) {
        Line line{vertex[i], vertex[i + 1]};
        Vector p{line.get_segment_nearest_point(point)};
        double l{(p - point).length()};
        if (l < distance) {
            distance = l;
            result = p;
        }
    }

    Line line{vertex[poly_size - 1], vertex[0]};
    Vector p{line.get_segment_nearest_point(point)};
    double l{(p - point).length()};
    if (l < distance) {
        distance = l;
        result = p;
    }

    return result;
}

Vector Polygon::count_center() const {
    int n{static_cast<int>(vertex.size())};
    if (n <= 0)
        throw Polygon::NotEnoughPointsException{"The polygon has zero vertices"};

    Vector result;
    for (Vector v : vertex) {
        result += v;
    }
    result /= n;

    return result;
}

void Polygon::split_nearest_edge(const Vector &point) {
    Vector result;
    int ri{-1};
    double distance{std::numeric_limits<double>::infinity()};
    int poly_size{static_cast<int>(vertex.size())};
    if (poly_size < 2)
        throw Polygon::NotEnoughPointsException{"The polygon has less than two vertices"};

    for (int i = 0; i < poly_size - 1; i++) {
        Line line{vertex[i], vertex[i + 1]};
        Vector p{line.get_segment_nearest_point(point)};
        double l{(p - point).length()};
        if (l < distance) {
            distance = l;
            ri = i;
            result = p;
        }
    }
    Line line{vertex[poly_size - 1], vertex[0]};
    Vector p{line.get_segment_nearest_point(point)};
    double l{(p - point).length()};
    if (l < distance) {
        distance = l;
        ri = vertex.size() - 1;
        result = p;
    }

    if ((ri != -1) and (vertex[ri] != result) and (vertex[ri + 1] != result)) {
        vertex.insert(vertex.begin() + ri + 1, result);
    }
}

bool Polygon::is_point_inside(const Vector &point) const {
    int pointsCount{static_cast<int>(vertex.size()) - 1};
    if (pointsCount < 2)
        throw Polygon::NotEnoughPointsException{"The polygon has not enough vertices"};

    Line l{ Line::directed_line(point, Vector{0.0, 1e100})};
    int result{0};
    Vector v;
    for (int i = 0; i < pointsCount; i++) {
        Line line{vertex[i], vertex[i + 1]};
        result += l.cross_segment_segment(line, v);
    }
    Line line{vertex[pointsCount], vertex[0]};
    result += l.cross_segment_segment(line, v);
    return result % 2 != 0;
}

bool Polygon::is_segment_inside(const Line &segment, size_t excludeLine1, size_t excludeLine2) const {
    size_t pointsCount{vertex.size()};

    if (pointsCount < 3)
        throw Polygon::NotEnoughPointsException{"The polygon has not enough vertices"};

    for (size_t i = 0; i < pointsCount; i++) {
        if (i != excludeLine1 && i != excludeLine2) {
            Vector p1{vertex[i]};
            Vector p2{vertex[i + 1 < pointsCount ? i + 1 : 0]};
            Vector p;
            if ((Line(p1, p2).cross_segment_segment(segment, p)) and
                ((p1 - p).square_length() > POLY_SPLIT_EPS) and
                ((p2 - p).square_length() > POLY_SPLIT_EPS)) {
                return 0;
            }
        }
    }
    return is_point_inside(segment.get_point_along(0.5));
}

bool Polygon::is_clockwise() const {
    if (vertex.size() < 2)
        throw Polygon::NotEnoughPointsException{"The polygon has not enough vertices"};

    double sum{0};
    int t{static_cast<int>(vertex.size()) - 1};
    for (int i = 0; i < t; i++) {
        sum += (vertex[i + 1].x - vertex[i].x) * (vertex[i + 1].y + vertex[i].y);
    }
    sum += (vertex[0].x - vertex[t].x) * (vertex[0].y + vertex[t].y);
    return sum <= 0;
}


bool Polygon::get_cut(const Line &l1, const Line &l2, double s,
            const Polygon &poly1, const Polygon &poly2,
            Line &cut) {
    double sn1{s + poly2.count_square_signed()};
    double sn2{s + poly1.count_square_signed()};

    bool success{false};

    if (sn1 > 0) {
        Polygons res{l1, l2};

        if (res.find_cut_line(sn1, cut))
            success = true;
    } else if (sn2 > 0) {
        Polygons res{l2, l1};

        if (res.find_cut_line(sn2, cut)) {
            cut = cut.reverse();
            success = true;
        }
    }

    return success;
}

void Polygon::push_back(const Vector &v) {
    vertex.push_back(v);
}