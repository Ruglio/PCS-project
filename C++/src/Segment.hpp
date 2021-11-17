#ifndef SEGMENT_H
#define SEGMENT_H

#include "Point.hpp"

using namespace Eigen;

class ISegment
{
    public:
        virtual void setStart(const Point& start) = 0;
        virtual const Point& getStart() const = 0;
        virtual Point& getStart() = 0;  // non-const because in some case we have to change the labels

        virtual void setEnd(const Point& end) = 0;
        virtual const Point& getEnd() const = 0;
        virtual Point& getEnd() = 0;    // non-const because in some case we have to change the labels

        virtual void setSegment(const Point& start, const Point& end) = 0;

        virtual const Vector2d& computeTangent() = 0;
        virtual const Vector2d& getTangent() const = 0;

        virtual int pointOnTheRightSide(const Point& point) const  = 0;
};

class Segment : public ISegment
{
    private:
        Point _start;
        Point _end;
        Vector2d _tangent;

    public:
        Segment(const Point& start = Point(), const Point& end = Point());

        void setStart(const Point& start) {_start = start;}
        const Point& getStart() const {return _start;}
        Point& getStart() {return _start;}  // non-const because in some case we have to change the labels

        void setEnd(const Point& end) {_end = end;}
        const Point& getEnd() const {return _end;}
        Point& getEnd() {return _end;}      // non-const because in some case we have to change the labels

        void setSegment(const Point& start, const Point& end) {_start = start; _end = end;}
        const Vector2d& computeTangent();
        const Vector2d& getTangent() const {return _tangent;}
        int pointOnTheRightSide(const Point& point) const;

        Segment& operator = (const Segment& segment);
        friend bool operator == (const Segment& s1, const Segment& s2);
};

#endif
