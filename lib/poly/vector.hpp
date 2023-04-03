#pragma once

#include <cmath>
#include <ostream>
#include <vector>

#include "point.hpp"

struct Vector {
    Point p;
    double &x = p.x;
    double &y = p.y;

    Vector(const Point &p) {
        this->p = p;
    };

    Vector(const Vector &v) {
        p = v.p;
    }

    Vector(double x=0.0f, double y=0.0f) {
        p.x = x;
        p.y = y;
    };

    void operator=(const Vector &v) {
        p = v.p;
    }

    Vector operator-() const {
        return Vector{-p};
    }

    Vector &operator+=(const Vector &v) {
        p += v.p;

        return *this;
    }

    Vector &operator-=(const Vector &v) {
        p -= v.p;

        return *this;
    }

    Vector &operator*=(double v) {
        p *= v;

        return *this;
    }

    Vector &operator/=(double v) {
        p /= v;

        return *this;
    }

    Vector operator-(const Vector &v) const {
        return Vector{p - v.p};
    }

    Vector operator+(const Vector &v) const {
        return Vector{p + v.p};
    }

    Vector operator*(const double v) const {
        return Vector{p * v};
    }

    Vector operator/(const double v) const {
        return Vector{p / v};
    }

    double dot(const Vector &v) const {
        return x * v.x + y * v.y;
    }

    double length(void) const {
        return sqrt(square_length());
    }

    double square_length(void) const {
        return p.square_distance({0, 0});
    }

    Vector norm(void) const {
        double l = length();
        if (l == 0)
            return Vector{};
        else
            return Vector{p / l};
    }

    bool operator==(const Vector &v) const {
        return p == v.p;
    }

    bool operator!=(const Vector &v) const {
        return p != v.p;
    }

    Vector abs() const {
        return Vector{p.abs()};
    }

    friend std::ostream& operator<<(std::ostream &out, const Vector &v) {
        out << v.p;
        return out;
    }
};

typedef std::vector<Vector> Vectors;
typedef std::vector<Vector>::iterator VecIter;
typedef std::vector<Vector>::const_iterator CVectIter;