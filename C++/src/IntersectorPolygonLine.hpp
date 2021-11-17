#ifndef INTERSECTORPOLYGONLINE_H
#define INTERSECTORPOLYGONLINE_H

#include <vector>
#include <unordered_map>
#include "Polygon.hpp"
#include "Point.hpp"
#include "Intersector1D1D.hpp"
#include <gtest/gtest_prod.h>

namespace IntersectorPolygonLineNamespace {

class IIntersectorPolygonLine
{
    private:
        virtual bool checkInConicCombination(const Vector2d& line, const Vector2d& v1, const Vector2d& v2, int& flag) const = 0;
        virtual void extendPolygonIfEndpointsOnEdge(int& numPoly, const int& firstIntersectionId, const int& secondIntersectionId, const bool& forwardDirection) = 0;

    public:
        virtual const vector<Point>& findIntersectionVertices() = 0;
        virtual const vector<Polygon>& findPolygons() = 0;
        virtual const vector<Point>& findNewPoints() = 0;

        virtual const vector<Polygon>& getExtendedPolygons() = 0;

        virtual bool getStartFound() const = 0;
        virtual bool getEndFound() const = 0;

};

class IntersectorPolygonLine : public IIntersectorPolygonLine
{
    private: 
        IIntersector1D1D& _intersector;
        IPolygon& _polygon;
        ISegment& _line;

        vector<Point> _intersectionVertices;
        vector<Point> _newPoints;

        vector<Polygon> _extendedNewPolygons;
        vector<Polygon> _newPolygons;

        vector<int> _intersectionIdToSegmentId;
        vector<int> _segmentIdToIntersectionId;
        vector<bool> _foundVertex;
        bool _startFound = false;
        bool _endFound = false;
        vector<int> _flag;
        vector<bool> _parallelIntersections;

        multimap<double, Point> _mmapParametricCoordinateToIntersectionPoint;
        multimap<double, int> _mmapParametricCoordinateToSegmentId;
        map<int, double> _mapSegmentIdToParametricCoordinate;
        map<int,double> _mapIntersectionIdToParametricCoordinate;

    public:
        IntersectorPolygonLine(IIntersector1D1D& intersector, IPolygon& polygon, ISegment& segment);

        const vector<Point>& findIntersectionVertices();
        const vector<Polygon>& findPolygons();
        const vector<Point>& findNewPoints();

        const vector<Polygon>& getExtendedPolygons() {return _extendedNewPolygons;}
        bool getStartFound() const {return _startFound;}
        bool getEndFound()  const {return _endFound;}

    private:
        bool checkInConicCombination(const Vector2d& line, const Vector2d& v1, const Vector2d& v2, int& flag) const;

        //N.B: per poter fare il test di un metodo privato in forma diretta serve avere un test friend che possa accedere ai membri privati della classe
        FRIEND_TEST(TestIntersectorPolygonLine, TestCheckInConicCombination);
        void extendPolygonIfEndpointsOnEdge(int& numPoly, const int& firstIntersectionId, const int& secondIntersectionId, const bool& forwardDirection);
};



}

#endif
