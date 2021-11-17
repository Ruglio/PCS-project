#ifndef INTERSECTOR1D1D_HPP
#define INTERSECTOR1D1D_HPP

#include "Eigen"
#include "iostream"
#include "MACROS.h"
#include "Segment.hpp"

using namespace std;
using namespace Eigen;

class IIntersector1D1D
{
public:
    enum Type
    {
        NoIntersection = 0,
        IntersectionOnLine = 1,
        IntersectionOnSegment = 2,
        IntersectionParallelOnLine = 3,
        IntersectionParallelOnSegment = 4,
    };
    enum Position
    {
        Begin = 0,
        Inner = 1,
        End = 2,
        Outer = 3
    };

     public:
        virtual void SetFirstSegment(const Vector2d& origin, const Vector2d& end) = 0;
        virtual void SetSecondSegment(const Vector2d& origin, const Vector2d& end) = 0;
        virtual bool ComputeIntersection() = 0;
        virtual const Vector2d& ParametricCoordinates() = 0;
        virtual const double& FirstParametricCoordinate() = 0;
        virtual const double& SecondParametricCoordinate() = 0;
        virtual const Position& PositionIntersectionInFirstEdge() = 0;
        virtual const Position& PositionIntersectionInSecondEdge() = 0;
        virtual const Type& TypeIntersection() = 0;
        virtual Vector2d IntersectionFirstParametricCoordinate(const Vector2d& origin,const Vector2d& end) const = 0;
        virtual Vector2d IntersectionSecondParametricCoordinate(const Vector2d& origin,const Vector2d& end) const = 0;
};

class Intersector1D1D : public IIntersector1D1D
{
    public:
        Type type;

    private:
        Position positionIntersectionFirstEdge;
        Position positionIntersectionSecondEdge;

        Vector2d resultParametricCoordinates;
        Vector2d originFirstSegment;
        //right side of the system: it is equal to the origin of the second segment - the origin of the first segment
        Vector2d rightHandSide;
        //matrix made up of the 2 segment tangent vectors
        Matrix2d matrixTangentVector;

    public:
        Intersector1D1D();

        //FirstSegment must be set before the second because then we use the attribute "originFirtsSegment"
        void SetFirstSegment(const Vector2d& origin, const Vector2d& end) {matrixTangentVector.col(0) = end - origin; originFirstSegment = origin; }
        void SetSecondSegment(const Vector2d& origin, const Vector2d& end) {matrixTangentVector.col(1) = origin - end; rightHandSide = origin - originFirstSegment; }

        ///Compute the intersections between the line of the first edge and the second edge and returns the parametric coordinates and the intersection type
        ///The first parametric coordinate refers to the first tangentVector and ...
        ///@note In case of parallelism both the parametric coordinates refers to the first edge
        bool ComputeIntersection();

        const Vector2d& ParametricCoordinates() {return resultParametricCoordinates;}
        const double& FirstParametricCoordinate() {return resultParametricCoordinates(0);}
        const double& SecondParametricCoordinate() {return resultParametricCoordinates(1);}

        const Position& PositionIntersectionInFirstEdge(){return positionIntersectionFirstEdge;}
        const Position& PositionIntersectionInSecondEdge(){return positionIntersectionSecondEdge;}

        const Type& TypeIntersection() {return type;}

        Vector2d IntersectionFirstParametricCoordinate(const Vector2d& origin,const Vector2d& end) const {return (1 - resultParametricCoordinates(0)) * origin + resultParametricCoordinates(0) * end; }
        Vector2d IntersectionSecondParametricCoordinate(const Vector2d& origin,const Vector2d& end) const {return (1 - resultParametricCoordinates(1)) * origin + resultParametricCoordinates(1) * end; }
};

#endif // INTERSECTOR1D1D_H

