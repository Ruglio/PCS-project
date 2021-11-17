#include "Polygon.hpp"
#include "Eigen"

using namespace std;

Polygon::Polygon()
{
    _numberVertices = 0;
    _vertices.reserve(3);
}

Polygon::Polygon(const vector<Point>& vertices)
{
    _numberVertices = vertices.size();
    _vertices.resize(_numberVertices);
    _vertices = vertices;

    _edges.resize(_numberVertices);
    for (unsigned int n = 0; n < _numberVertices; n++)
    {
        if (n == _numberVertices - 1)
            _edges[n] = Segment(_vertices[n], _vertices[0]);
        else
            _edges[n] = Segment(_vertices[n], _vertices[n + 1]);
    }
}

void Polygon::setVertexAtPosition(const Point& vertex, const int& position)
{
    if (position < 0 || position >= (int)_numberVertices)
        throw runtime_error("Error: Vertex poition is not present");

    _vertices[position] = vertex;
}

void Polygon::appendVertex( const Point& vertex)
{
    _vertices.push_back(vertex);
    _numberVertices = _vertices.size();
}

void Polygon::insertVertexAtPosition(const Point& vertex, const int& position)
{
    vector<Point>::iterator PointIt;
    PointIt = _vertices.begin() + position;
    _vertices.insert(PointIt, vertex);
    _numberVertices = _vertices.size();

    //insert newEdge
    Segment newSegment(_vertices[position], _vertices[(position + 1)%_numberVertices]);
    vector<Segment>::iterator EdgeIt;
    EdgeIt = _edges.begin() + position;
    _edges.insert(EdgeIt, newSegment);

    //fix adjacent edges
    _edges[(position - 1)%_numberVertices].setEnd(_vertices[position]);
    _edges[(position + 1)%_numberVertices].setStart(_vertices[(position + 1)%_numberVertices]);
}

int Polygon::nextVertexId(unsigned int id) const
{
    if (id < 0 || id >= _numberVertices)
        throw runtime_error("Error: Vertex id is not present");

    if (id == _numberVertices - 1)
        return 0;
    else
        return id + 1;
}

double Polygon::ComputeArea() const    // algoritmo di Gauss
{
    double area = 0;
    for (unsigned int i = 0; i < _numberVertices; i++)
    {
        if (i == _numberVertices - 1)
            area += _vertices[i].getCoordinates()(1) * (_vertices[i - 1].getCoordinates()(0) - _vertices[0].getCoordinates()(0));
        else if (i == 0)
            area += _vertices[i].getCoordinates()(1) * (_vertices[_numberVertices - 1].getCoordinates()(0) - _vertices[i + 1].getCoordinates()(0));
        else
            area += _vertices[i].getCoordinates()(1) * (_vertices[i - 1].getCoordinates()(0) - _vertices[i + 1].getCoordinates()(0));
    }

    return abs(area)/2;
}

bool Polygon::pointInPolygon(const Point &point) // only for convex polygons because Project's 3 domain is supposed convex
{
    unsigned int i;
    bool val = 1; //by default the point is inside the polygon

    for(i = 0; i < _numberVertices && val == 1; i++)
    {
        // if the point point is to the right of some edge, it is not inside the polygon, so val is set to 0
        if (_edges[i].pointOnTheRightSide(point) == 1)
            val = 0;
    }

    return val;
}

Polygon &Polygon::operator =(const Polygon &polygon)
{
    _numberVertices = polygon._numberVertices;
    _vertices.resize(_numberVertices);
    _vertices = polygon._vertices;

    _edges.resize(_numberVertices);
    _edges = polygon._edges;

    return *this;
}

void Polygon::setVertexLabelAtPosition(const int &position, int label)
{
    if (position < 0 || position >= (int)_numberVertices)
        throw runtime_error("Error: Vertex poition is not present");

    _vertices[position].setPointLabel(label);
}

void Polygon::setVertexLabels(const vector<unsigned int> &polygonLabels)
{
    if (polygonLabels.size() != _numberVertices)
        throw runtime_error("Error: size dimensions must agree");

    for(unsigned int i = 0; i < _numberVertices ; i++)
    {
        int label = polygonLabels[i];
        _vertices[i].setPointLabel(label);
    }
}

void Polygon::setDefaultVertexLabels()
{
    for(unsigned int i = 0; i < _numberVertices ; i++)
    {
        _vertices[i].setPointLabel(i);
        _edges[i].getStart().setPointLabel(i);
        _edges[i].getEnd().setPointLabel((i+1)%_numberVertices);
    }
}

int Polygon::isPolygonOnTheRightSide(const Segment &line) const
{
    int side = 0;
    int numPointsOnTheRight = 0;
    int numPointsOnTheLeft  = 0;
    //controlling if the vertices are on on the right or on the left of the segment
    for (unsigned int i = 0; i< _numberVertices; i++)
    {
        if ( line.pointOnTheRightSide(_vertices[i]) == 1)
            numPointsOnTheRight ++;
        if ( line.pointOnTheRightSide(_vertices[i]) == -1)
            numPointsOnTheLeft ++;
    }
    if ( numPointsOnTheRight > 0  &&  numPointsOnTheLeft == 0) //polygon is on the right
        side = 1;

    if ( numPointsOnTheRight == 0 &&  numPointsOnTheLeft > 0) //polygon is on the left
        side = -1;

    return side;
}

void Polygon::buildUpPolygonEdges()
{
    _edges.resize(_numberVertices);

    for (unsigned int n = 0; n < _numberVertices; n++)
    {
        if (n == _numberVertices - 1)
            _edges[n] = Segment(_vertices[n], _vertices[0]);
        else
            _edges[n] = Segment(_vertices[n], _vertices[n + 1]);
    }
}
