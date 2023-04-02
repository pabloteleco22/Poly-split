#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <ostream>
#include <vector>

const double POLY_SPLIT_EPS = 1E-6;

struct Vector {
    double x, y;

    Vector(double x = 0.0f, double y = 0.0f) : x(x), y(y) {};

    inline Vector operator-() const {
        return Vector{-x, -y};
    }

    inline Vector &operator+=(const Vector &v) {
        x += v.x;
        y += v.y;

        return *this;
    }

    inline Vector &operator-=(const Vector &v) {
        x -= v.x;
        y -= v.y;

        return *this;
    }

    inline Vector &operator*=(double v) {
        x *= v;
        y *= v;

        return *this;
    }

    inline Vector &operator/=(double v) {
        x /= v;
        y /= v;

        return *this;
    }

    inline Vector operator-(const Vector &v) const {
        return Vector{x - v.x, y - v.y};
    }

    inline Vector operator+(const Vector &v) const {
        return Vector{x + v.x, y + v.y};
    }

    inline Vector operator*(const double v) const {
        return Vector{x * v, y * v};
    }

    inline Vector operator/(const double v) const {
        return Vector{x / v, y / v};
    }

    inline double dot(const Vector &v) const {
        return x * v.x + y * v.y;
    }

    inline double length(void) const {
        return sqrt(x * x + y * y);
    }

    inline double squareLength(void) const {
        return x * x + y * y;
    }

    inline Vector norm(void) const {
        double l = length();
        if (l == 0)
            return Vector{};
        else
            return Vector{x / l, y / l};
    }

    inline bool operator ==(const Vector &v) const {
        return x == v.x && y == v.y;
    }

    inline bool operator !=(const Vector &v) const {
        return fabs(x - v.x) >= POLY_SPLIT_EPS || fabs(y - v.y) >= POLY_SPLIT_EPS;
    }

    inline Vector abs() const {
        return Vector{fabs(x), fabs(y)};
    }

    friend std::ostream& operator<< (std::ostream &out, const Vector &v) {
        out << "(" << v.x << ", " << v.y << ")";
        return out;
    }
};

typedef std::vector<Vector> Vectors;
typedef std::vector<Vector>::iterator VecIter;
typedef std::vector<Vector>::const_iterator CVectIter;

#endif // VECTOR_H
