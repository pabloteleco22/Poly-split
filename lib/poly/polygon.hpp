#ifndef POLYGON_H
#define POLYGON_H

#include "line.hpp"
#include <string>
#include <exception>

class Polygon {
private:
    Vectors poly;

public:
    Polygon();

    Polygon(const Vectors &v);

    class VoidPolygonException : public std::exception {
        std::string message{"The polygon has no vertices"};
        public:
            VoidPolygonException();
            VoidPolygonException(const std::string &message);
            VoidPolygonException(const char *message);
            const char *what() const noexcept override;
    };

    /**
     * @brief Returns the polygon area
    */
    double countSquare(void) const;
    double countSquare_signed(void) const;

    /**
     * @brief Split the polygon into two parts with the specified area.
     *
     * @param
     * square: The area of the result poly2.
     * @param
     * poly1: The resulting polygon containing the area that has
     * not been left poly2.
     * @param
     * poly2: The resulting polygon with the specified area.
     * @param
     * cutLine: The line dividing the two polygons.
     * 
     * @returns
     * true: if it is possible.
     * false: if it is not possible.
    */
    bool split(double square, Polygon &poly1, Polygon &poly2, Line &cutLine) const;

    double findDistance(const Vector &point) const;
    Vector findNearestPoint(const Vector &point) const;

    Vector countCenter(void) const;

    void splitNearestEdge(const Vector &point);

    int isPointInside(const Vector &point) const;
    int isClockwise(void) const;

    const Vectors &getVectors(void) const {
        return poly;
    }

    void push_back(const Vector &v) {
        poly.push_back(v);
    }

    int empty(void) const {
        return poly.empty();
    }

    Vector &operator [](size_t index) {
        return poly[index];
    }

    Polygon &operator =(const Polygon &p) {
        poly = p.poly;
        return *this;
    }

    Vector operator [](size_t index) const {
        return poly[index];
    }

    void clear(void) {
        poly.clear();
    }

    size_t size(void) const {
        return poly.size();
    }
};

#endif // POLYGON_H
