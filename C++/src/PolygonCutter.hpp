#ifndef POLYGONCUTTER_H
#define POLYGONCUTTER_H

#include "Intersector1D1D.hpp"
#include "IntersectorPolygonLine.hpp"

using namespace IntersectorPolygonLineNamespace;

namespace PolygonCutterNamespace {

class IPolygonCutter
{
    public:
        virtual const vector<Polygon>& cutPolygon() = 0;

        virtual const vector<Polygon>& getCuttedPolygons() const = 0;
        virtual const vector<Point>& getIntersectionVertices() const = 0;
        virtual const vector<Point>& getNewPoints() const = 0;

        virtual void showPolygon(const string filePath = "showPolygon.m") = 0;
};


class PolygonCutter: IPolygonCutter
{
    private:
        IIntersectorPolygonLine& _intersector;
        IPolygon& _polygon;
        ISegment& _cutter;

        vector<Polygon> _cuttedPolygons;
        vector<Point> _intersectionVertices;
        vector<Point> _newPoints;

    public:
        PolygonCutter(IIntersectorPolygonLine& intersector, IPolygon& polygon, ISegment& segment);

        const vector<Polygon>& cutPolygon();

        const vector<Polygon>& getCuttedPolygons() const {return _cuttedPolygons;};
        const vector<Point>& getIntersectionVertices() const {return _intersectionVertices;}
        const vector<Point>& getNewPoints() const {return _newPoints;}

        void showPolygon(const string filePath = "showPolygon.m");
};

}

#endif
