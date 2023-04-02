#ifndef POLYGON_H
#define POLYGON_H

#include "line.hpp"
#include <string>
#include <exception>

class Polygon {
private:
    Vectors vertex;

public:
    Polygon();

    Polygon(const Vectors &v);

    class NotEnoughPointsException : public std::exception {
        std::string message{"The polygon has not enough vertices"};
        public:
            NotEnoughPointsException();
            NotEnoughPointsException(const std::string &message);
            NotEnoughPointsException(const char *message);
            const char *what() const noexcept override;
    };
/**
     * @brief Returns the polygon area.
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

    /**
     * @brief Returns the distance between the nearest point of the polygon
     * and the point passed by parameters.
     * 
     * @throws
     * Polygon::VoidPolygonExcception: if the polygon contains no points.
    */
    double findDistance(const Vector &point) const;

    /**
     * @brief Returns the point of the polygon nearest to the one passed by
     * parameters.
     * 
     * @throws
     * Polygon::VoidPolygonExcception: if the polygon contains no points.
    */
    Vector findNearestPoint(const Vector &point) const;

    /**
     * @brief Returns the centroid of the polygon.
     * 
     * @throws
     * Polygon::VoidPolygonExcception: if the polygon contains no points.
    */
    Vector countCenter(void) const;

    /**
     * @brief Generates a new vertex in the polygon at the nearest point
     * between the passed by parameter and the edge of the polygon.
    */
    void splitNearestEdge(const Vector &point);

    /**
     * @brief Returns true if the point passed by parameters is contained
     * within the edges of the polygon. 
    */
    bool isPointInside(const Vector &point) const;
    
    /**
     * @brief Returns true if the vertex are in clock wise order.
    */
    bool isClockwise(void) const;

    const Vectors getVectors(void) const {
        return vertex;
    }

    /**
     * @brief If the point passed by parameters was not a vertex of the
     * polygon, now it is.
    */
    void push_back(const Vector &point);

    /**
     * @brief Returns true if the polygon has no vertex.
    */
    bool empty(void) const {
        return vertex.empty();
    }

    Polygon &operator=(const Polygon &p) {
        vertex = p.vertex;
        return *this;
    }

    Vector operator[](size_t index) const {
        return vertex[index];
    }

    Vector &operator[](size_t index) {
        return vertex[index];
    }

    /**
     * @brief Removes all the vertex of the polygon.
    */
    void clear(void) {
        vertex.clear();
    }

    /**
     * @brief Returns the number of vertex of the polygon.
    */
    size_t size(void) const {
        return vertex.size();
    }
};

#endif // POLYGON_H
