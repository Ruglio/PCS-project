#include "Segment.hpp"
#include <iostream>

using namespace Eigen;

Segment::Segment(const Point &start, const Point &end)
    : _start(start), _end(end)
{
    _tangent = end.getCoordinates() - start.getCoordinates();
}

const Vector2d &Segment::computeTangent()
{
    _tangent = (_end - _start).getCoordinates();
    return _tangent;
}

int Segment::pointOnTheRightSide(const Point &point) const
{
    int val;
    double crossProduct;

    Segment segment(_start, point);

    //computing cross product
    crossProduct =(_tangent.x() * segment.getTangent().y()) - (segment.getTangent().x() * _tangent.y());

    if (crossProduct < - POINT_TOLERANCE)
    {
       val = 1;     //si trova a destra
       return val;
    }

    else if(crossProduct >  POINT_TOLERANCE)
    {
        val = -1;   //si trova a sinistra
        return val;
    }
    else
    {
        val = 0;    // il punto è sulla stessa retta del segmento
        return val;
    }

}

Segment &Segment::operator =(const Segment &segment)
{
    _start = segment._start;
    _end = segment._end;
    _tangent = segment._tangent;
    return *this;
}

bool operator == (const Segment& s1, const Segment& s2)
{
    return (s1.getStart() == s2.getStart() && s1.getEnd() == s2.getEnd());
}
