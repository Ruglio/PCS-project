#include "PolygonCutter.hpp"
#include "fstream"


namespace PolygonCutterNamespace {

PolygonCutter::PolygonCutter(IIntersectorPolygonLine& intersector, IPolygon &polygon, ISegment &segment)
    : _intersector{intersector}, _polygon{polygon}, _cutter{segment}
{
}


const vector<Polygon> &PolygonCutter::cutPolygon()
{
    _intersectionVertices  = _intersector.findIntersectionVertices();
    _newPoints = _intersector.findNewPoints();
    _cuttedPolygons = _intersector.findPolygons();

    return _cuttedPolygons;
}


void PolygonCutter::showPolygon(const string filePath)
{
    if (_cuttedPolygons.empty())
        throw runtime_error("First you need to find sub-polygons");


    ofstream of;
    of.open (filePath);
    const vector<Point>& vertices = _polygon.getVertices();

    of << "width = 1.0;" << endl
       << "labs = 0:" << vertices.size()-1 << ';' << endl
       << "labsInt = 0:" << _intersectionVertices.size()-1 << ';' << endl
       << "points = [" << endl;

    for (unsigned int i = 0; i < vertices.size(); i++)
        of << "\t" << vertices[i].getCoordinates()[0] << ", " << vertices[i].getCoordinates()[1] << endl;
    of << "];" << endl;

    of << "polygon = polyshape(points);" << endl
       << "segment = [" << endl
       << "\t" << _cutter.getStart().getCoordinates()[0] << ", " << _cutter.getStart().getCoordinates()[1] << endl
       << "\t" << _cutter.getEnd().getCoordinates()[0] << ", " << _cutter.getEnd().getCoordinates()[1] << endl
       << "];" << endl
       << "intersection = [" << endl;

    for (unsigned int i = 0; i < _intersectionVertices.size(); i++)
        of << "\t" << _intersectionVertices[i].getCoordinates()[0] << ", " << _intersectionVertices[i].getCoordinates()[1] << endl;
    of << "];" << endl;

    of << "figure;" << endl
       << "hold on;" << endl
       << "plot(polygon, 'FaceColor', 'w', 'LineWidth', width);" << endl
       << "plot([segment(1,1), segment(2,1)], [segment(1,2), segment(2,2)], 'r--');" << endl
       << "plot(points(:, 1),points(:, 2), 'ko');" << endl
       << "plot(intersection(:, 1), intersection(:, 2), 'rs');" << endl
       << "plot(segment(:, 1), segment(:, 2), 'r.', 'MarkerSize', 9);" << endl
       << "text(points(:,1), points(:,2), string(labs), 'VerticalAlignment', 'top', 'HorizontalAlignment', 'left');" << endl
       << "text(intersection(:,1), intersection(:,2), string(labsInt), 'VerticalAlignment', 'bottom', 'HorizontalAlignment', 'right', 'Color', 'r');" << endl
       << "hold off;" << endl << endl;

    of << "figure;" << endl
       << "hold on;" << endl;
    for (unsigned int n = 0; n < _cuttedPolygons.size(); n++)
    {
        of << "points" << n+1 << " = [" << endl;
        const vector<Point>& points = _cuttedPolygons[n].getVertices();
        for (unsigned int i = 0; i < _cuttedPolygons[n].getNumberVertices(); i++)
            of << "\t" << points[i].getCoordinates()[0] << ", " << points[i].getCoordinates()[1] << endl;

        of << "];" << endl;
        of << "polygon" << n+1 << " = polyshape(points" << n+1 << ");" << endl
           << "plot(polygon" << n+1 << ", 'LineWidth', width);" << endl << endl;
    }
    of << "text(points(:,1), points(:,2), string(labs), 'VerticalAlignment', 'top', 'HorizontalAlignment', 'left');" << endl
       << "text(intersection(:,1), intersection(:,2), string(labsInt), 'VerticalAlignment', 'bottom', 'HorizontalAlignment', 'right', 'Color', 'r');" << endl
       << "hold off;" << endl;

    of.close();
}

}
