#ifndef POINT_H
#define POINT_H

#include "Eigen"
#include "MACROS.h"

using namespace Eigen;

class Point
{
    private:
        Vector2d _coordinates;
        int _label = -2;

    public:
        Point(const double x = 0.0, const double y = 0.0);
        Point(Vector2d coordinates);
        Point(const Point& point);

        void setCoordinates(const double x, const double y) {_coordinates(x, y);}
        const Vector2d& getCoordinates() const {return _coordinates;}
        int getPointLabel() const{ return _label;}
        void setPointLabel(const int label);

        Point& operator = (const Point& point);
        Point operator + (const Point& point);
        Point operator - (const Point& point);

        friend bool operator == (const Point& p1, const Point& p2);
        friend bool operator != (const Point& p1, const Point& p2);
};

#endif
