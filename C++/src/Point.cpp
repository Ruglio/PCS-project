#include "Point.hpp"
#include "Eigen"

using namespace Eigen;

Point::Point(const double x, const double y)
    : _coordinates(x, y)
{
}

Point::Point(Vector2d coordinates)
{
    _coordinates = coordinates;
}

Point::Point(const Point &point)
{
    _coordinates = point._coordinates;
    _label = point._label;
}

void Point::setPointLabel(int label)
{
    _label = label;
}

Point &Point::operator =(const Point &point)
{
    _coordinates = point.getCoordinates();
    _label = point.getPointLabel();
    return *this;
}

Point Point::operator +(const Point &point)
{
    return Point(_coordinates + point.getCoordinates());
}

Point Point::operator -(const Point &point)
{
    return Point(_coordinates - point.getCoordinates());
}

bool operator == (const Point& p1, const Point& p2)
{
    double maxnorm= p1.getCoordinates().norm();
    double norm2= p2.getCoordinates().norm();
    if( norm2 > maxnorm)
        maxnorm = norm2;

    return ((p1.getCoordinates() - p2.getCoordinates()).norm()<= POINT_TOLERANCE*maxnorm );
}

bool operator != (const Point& p1, const Point& p2)
{
    return !(p1 == p2);
}


