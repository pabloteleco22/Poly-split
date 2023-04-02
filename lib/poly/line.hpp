#ifndef LINE_H
#define LINE_H

#include "vector.hpp"

class Line {
    private:
        double a{0}; // -Increase of y
        double b{0}; // Increase of x
        double c{0}; // Determinant of the segment
        Vector start, end;

    public:
        Line();
        Line(const Vector &start, const Vector &end);
        Line(double a, double b, double c);

        /**
         * @brief It returns the start point of the segment
        */
        Vector getStart() const;

        /**
         * @brief It returns the end point of the segment
        */
        Vector getEnd() const;

        /**
         * @brief It returns the length of the segment
        */
        double length() const;

        /**
         * @brief It returns the square of the length of the segment
        */
        double squareLength() const;

        /**
         * @brief It returns the same segment but the start point is
         * the new end point and vice versa
        */
        Line reverse() const;

        /**
         * @brief Returns a point on the line one distance t away from
         * the start point
        */
        Vector getPointAlong(double t) const;

        /**
         * @brief Returns the distance between the point and the line
        */
        double getDistance(const Vector &point) const;

        /**
         * @brief Returns the nearest point from the line
        */
        Vector getLineNearestPoint(const Vector &point) const;

        /**
         * @brief Returns the nearest point from the segment,
         * which means that it takes into account the start
         * and end points
        */
        Vector getSegmentNearestPoint(const Vector &point) const;

        /**
         * @brief Returns if the point is over, under or in the line
         * 
         * @returns
         *  1 if above,
         *  0 if in,
         *  -1 if below
        */
        int pointSide(const Vector &point) const;

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
        bool crossLineSegment(const Line &line, Vector &result) const;

        /**
         * @brief Returns whether the thw segments intersect and
         * the point of intersection between them
         * 
         * @param
         * result: The intersection point.
         * 
         * @return If the line and the segment intersect
        */
        bool crossSegmentSegment(const Line &line, Vector &result) const;

        /**
         * @brief Returns whether the two lines intersect and
         * the point of intersection between them
         * 
         * @param
         * result: The intersection point.
         * 
         * @return If the line and the segment intersect
        */
        bool crossLineLine(const Line &line, Vector &result) const;

        bool operator==(const Line &other) const;

        /**
         * @brief Returns true if l1 and l2 are the same line
        */
        static bool is_same(const Line &l1, const Line &l2);

        /**
         * @brief Returns the bisector between the two lines
        */
        static Line getBisector(const Line &l1, const Line &l2);

        /**
         * @brief Returns the tangent of the angle between the two lines in radians
        */
        static double getTanAngle(const Line &l1, const Line &l2);

        /**
         * @brief Returns a line from a point and a vector
         * 
         * @param
         * p: Point
         * @param
         * d: Vector
        */
        static Line directedLine(const Vector &p, const Vector &d);

        friend std::ostream& operator<< (std::ostream &out, const Line &l) {
            out << "[" << l.a << ", " << l.b << ", " << l.c << "]-{" << l.start << ", " << l.end << "}";
            return out;
        }
};

#endif // LINE_H
