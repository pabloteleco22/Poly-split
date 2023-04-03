#pragma once

#include <cmath>
#include <ostream>
#include <vector>

const double POLY_SPLIT_EPS = 1E-6;

struct Point {
    double x, y;

    Point(double x = 0.0f, double y = 0.0f) : x(x), y(y) {};

    Point operator-() const {
        return Point{-x, -y};
    }

    Point &operator+=(const Point &p) {
        x += p.x;
        y += p.y;

        return *this;
    }

    Point &operator-=(const Point &p) {
        x -= p.x;
        y -= p.y;

        return *this;
    }

    Point &operator*=(double p) {
        x *= p;
        y *= p;

        return *this;
    }

    Point &operator/=(double p) {
        x /= p;
        y /= p;

        return *this;
    }

    Point operator-(const Point &p) const {
        return Point{x - p.x, y - p.y};
    }

    Point operator+(const Point &p) const {
        return Point{x + p.x, y + p.y};
    }

    Point operator*(const double p) const {
        return Point{x * p, y * p};
    }

    Point operator/(const double p) const {
        return Point{x / p, y / p};
    }

    bool operator==(const Point &p) const {
        return x == p.x && y == p.y;
    }

    bool operator!=(const Point &p) const {
        return fabs(x - p.x) >= POLY_SPLIT_EPS || fabs(y - p.y) >= POLY_SPLIT_EPS;
    }

    double distance(const Point &p) const {
        return sqrt(square_distance(p));
    }

    double square_distance(const Point &p) const {
        double dx = fabs(x - p.x);
        double dy = fabs(y - p.y);

        return dx * dx + dy * dy;
    }

    Point abs() const {
        return Point{fabs(x), fabs(y)};
    }

    friend std::ostream& operator<<(std::ostream &out, const Point &v) {
        out << "(" << v.x << ", " << v.y << ")";
        return out;
    }
};

typedef std::vector<Point> Points;
typedef std::vector<Point>::iterator PointIter;
typedef std::vector<Point>::const_iterator CPointIter;