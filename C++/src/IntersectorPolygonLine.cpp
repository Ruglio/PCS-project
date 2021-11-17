#include "IntersectorPolygonLine.hpp"
#include "MACROS.h"

using namespace std;

namespace IntersectorPolygonLineNamespace {

IntersectorPolygonLine::IntersectorPolygonLine(IIntersector1D1D &intersector, IPolygon &polygon, ISegment &segment)
    : _intersector(intersector), _polygon(polygon), _line(segment)
{
    unsigned int numberVertices = polygon.getNumberVertices();
    _segmentIdToIntersectionId.resize(numberVertices);
    _foundVertex.resize(numberVertices);
    _flag.resize(numberVertices);
    _parallelIntersections.resize(numberVertices);

    // set default values for these support attributes that helps cutting the polygon
    for (unsigned int i = 0; i < numberVertices; i++)
    {
        _segmentIdToIntersectionId[i] = -1;
        _foundVertex[i] = false;
        _flag[i] = 0;
        _parallelIntersections[i] = false;
    }

    // set as the first segment of intersection the line since it remains the same all time
    _intersector.SetFirstSegment(segment.getStart().getCoordinates(), segment.getEnd().getCoordinates());
}


const vector<Point> &IntersectorPolygonLine::findIntersectionVertices()
{
    const vector<Segment> edges = _polygon.getEdges();
    _polygon.setDefaultVertexLabels();
    _line.getStart().setPointLabel(_polygon.getNumberVertices());
    _line.getEnd().setPointLabel(_polygon.getNumberVertices()+1);

    // cycle through all edges to find intersections
    for (unsigned int n = 0; n < _polygon.getNumberVertices(); n++)
    {
        _intersector.SetSecondSegment(edges[n].getStart().getCoordinates(), edges[n].getEnd().getCoordinates());
        if (_intersector.ComputeIntersection()) // true if there is intersection
        {
          // se il segmento di intersezione ed il lato sono paralleli
          if (_intersector.TypeIntersection() == Intersector1D1D::IntersectionParallelOnSegment
                    ||  _intersector.TypeIntersection() == Intersector1D1D::IntersectionParallelOnLine )
          {
                    _parallelIntersections[n] = true;
          }
          else
          {
                // finds intersection point and its parametric coordinate
                Vector2d intersection = _intersector.IntersectionFirstParametricCoordinate(_line.getStart().getCoordinates(), _line.getEnd().getCoordinates());
                double s = _intersector.FirstParametricCoordinate();
                // check if the point has been found before, this would mean there is intersection in a vertex
                if (_mmapParametricCoordinateToIntersectionPoint.find(s) == _mmapParametricCoordinateToIntersectionPoint.end())
                {
                    // insert values in a map or multimap so that they are ordered based on the key
                    _mmapParametricCoordinateToIntersectionPoint.insert(pair<double, Point>(s, Point(intersection)));
                    _mmapParametricCoordinateToSegmentId.insert(pair<double, int>(s, n));
                    _mapSegmentIdToParametricCoordinate.insert(pair<int, double>(n,s));
                }
                else // if there is intersection in a vertex
                {
                    // cerca se l intersezione sul vertice è su (lastVertex)(0) in modo da rendere il tutto ciclico
                    if ((n == _polygon.getNumberVertices()-1) && _mmapParametricCoordinateToSegmentId.find(s)->second == 0)
                    {
                        // nel caso imposto il _flag[0] invece di _flag[n] perche il flag è associato alla seconda intersezione per come è costruito il programma
                        bool isInConic = checkInConicCombination(_line.computeTangent(), edges[n].getTangent() , edges[0].getTangent(), _flag[0]);
                        // se isInConic = True significa che il vertice va inserito due volte
                        // le multimap sono utilizzate proprio per questo
                        if (isInConic)
                        {
                            _mmapParametricCoordinateToIntersectionPoint.insert(pair<double, Point>(s, Point(intersection)));
                            _mmapParametricCoordinateToSegmentId.insert(pair<double, int>(s, n));
                            _mapSegmentIdToParametricCoordinate.insert(pair<int, double>(n, s));
                        }
                        // in modo da far si che nel caso di intersezione sul vertice da contare una sola voltasia sempre il primo vertice ad avere l intersezione,
                        // in questo caso abbiamo il vertice (n)(0) e quindi l intersezione va segnata su n
                        else
                            _mmapParametricCoordinateToSegmentId.find(s)->second = (int)n;
                    }
                    else
                    {
                        bool isInConic = checkInConicCombination(_line.computeTangent(), edges[n-1].getTangent() , edges[n].getTangent(), _flag[n]);
                        if (isInConic)// se è true, aggiunge il punto alle strutture, duplicandolo, altrimenti non lo aggiunge
                        {
                            _mmapParametricCoordinateToIntersectionPoint.insert(pair<double, Point>(s, Point(intersection)));
                            _mmapParametricCoordinateToSegmentId.insert(pair<double, int>(s, n));
                            _mapSegmentIdToParametricCoordinate.insert(pair<int, double>(n,s));
                        }
                    }
                }
           }
        }
    }
    // maps and multimaps have been used because are needed elements ordered by a key

    // makes a vector with the Points from the map _mmapParametricCoordinateToIntersectionPoint<double,Point> and adds labels
    // in this way intersectionVertices are ordered by parametric coordinate
    int i = 0;
    multimap<double, Point>::const_iterator iterator1;
    for (iterator1 = _mmapParametricCoordinateToIntersectionPoint.begin(); iterator1 != _mmapParametricCoordinateToIntersectionPoint.end(); iterator1++)
    {
        _intersectionVertices.push_back(iterator1->second);
        _intersectionVertices[i].setPointLabel(_polygon.getNumberVertices()+2+i);
        i++;
    }

    int j = 0;
    multimap<double, int>::const_iterator iterator2;
    for (iterator2 = _mmapParametricCoordinateToSegmentId.begin(); iterator2 != _mmapParametricCoordinateToSegmentId.end(); iterator2++)
    {
        // if flag=-1 means that there is a double intersection on a vertex but that they are inserted in reverse order, so we
        // have to switch them
        if (_flag[iterator2->second] == -1)
        {
            int last = _intersectionIdToSegmentId.back();

            // bisogna scambiare i valori associati a parametric e iterator2->second in _segmentIdToIntersectionId
            _segmentIdToIntersectionId[iterator2->second] = _segmentIdToIntersectionId[last];
            _segmentIdToIntersectionId[last] = j;
            j++;

            // bisogna scambiare i valori in _intersectionIdToSegmentId
            unsigned int lastIndex = _intersectionIdToSegmentId.size() - 1;
            _intersectionIdToSegmentId[lastIndex] = iterator2->second;
            _intersectionIdToSegmentId.push_back(last);
        }
        else
        {
            _intersectionIdToSegmentId.push_back(iterator2->second);
            _segmentIdToIntersectionId[iterator2->second] = j;
            j++;// posizione dell'intersezione
        }
    }

    //loops through the intersection Points comparing if they are equal to any of the endpoints of the corrisponding segment,
    //If yes, it sets the attribute _label to that of the polygon vertex
    for(unsigned int k = 0; k < _intersectionIdToSegmentId.size(); k++)
    {
       int segmentPosition = _intersectionIdToSegmentId[k];

       const Point&  segmentStartPoint = _polygon.getEdges()[segmentPosition].getStart();
       if (_intersectionVertices[k] == segmentStartPoint )
            _intersectionVertices[k].setPointLabel(segmentStartPoint.getPointLabel());

       const Point&  segmentEndPoint = _polygon.getEdges()[segmentPosition].getEnd();
       if (_intersectionVertices[k] == segmentEndPoint )
           _intersectionVertices[k].setPointLabel(segmentEndPoint.getPointLabel());
    };

    //usando il vettore _segmentIdToIntersectionId e la mappa _mapSegmentIdToParametricCoordinate
    for ( unsigned int k = 0; k < _intersectionIdToSegmentId.size(); k++)
    {
        double parametricCoordinate = _mapSegmentIdToParametricCoordinate[_intersectionIdToSegmentId[k]];
        // map needed for the method extendPolygonIfEndpointsOnEdge
        _mapIntersectionIdToParametricCoordinate.insert(pair<int, double>(k, parametricCoordinate));
    }

    if (_intersectionVertices.size() % 2 == 1 )
       throw runtime_error ("Error: the number of intersection vertices should be even");

     return _intersectionVertices;
}


const vector<Polygon>& IntersectorPolygonLine::findPolygons()
{    
    // clear just to be sure it is empty
    _newPolygons.clear();
    _extendedNewPolygons.clear();
    const vector<Point>& vertices = _polygon.getVertices();
    int numPoly = 0;

    // cycle through all vertices till every of them has been visited
    for (unsigned int n = 0; n < _foundVertex.size(); n++)
    {
            if(_parallelIntersections[n] && _foundVertex[n] == false)
            {
                _foundVertex[n] = true;
                _foundVertex[(n+1)% _polygon.getNumberVertices()] = true;
            }
            else
            {//begin else

                if (_foundVertex[n] == false)   // il vertice non è stato ancora visitato
                {
                    _newPolygons.push_back(Polygon());
                    _extendedNewPolygons.push_back(Polygon());
                    unsigned int id = n;
                    bool forwardDirection;

                    // each while cycle ends when it returns to the start point, completing a cutted polygon
                    do
                    {
                        // if there is no intersection in that segment the algorithm append the vertex and goes to the next
                        if (_segmentIdToIntersectionId[id] == -1)
                        {
                            _newPolygons[numPoly].appendVertex(vertices[id]);
                            _extendedNewPolygons[numPoly].appendVertex(vertices[id]);
                            _foundVertex[id] = true;

                            id = _polygon.nextVertexId(id);
                        }
                        else    // there is intersection on that segment
                        {
                            // append the vertex to the cutted polygon
                            _newPolygons[numPoly].appendVertex(vertices[id]);
                            _extendedNewPolygons[numPoly].appendVertex(vertices[id]);
                            _foundVertex[id] = true;

                            // get the id (ordered in parametric coordinates) of the intersection point
                            int intersectionId = _segmentIdToIntersectionId[id];
                            // if the intersection is on the vertex we don t add it since the points are equal
                            if (_intersectionVertices[intersectionId] != vertices[id])
                            {
                                _newPolygons[numPoly].appendVertex(_intersectionVertices[intersectionId]);
                                _extendedNewPolygons[numPoly].appendVertex(_intersectionVertices[intersectionId]);
                            }

                            // intersection are in pair and they creates segment with intersection id even-odd that are inside the polygon
                            if (intersectionId % 2 == 0)    // if intersection id is even, the segment inside is (id),(id+1)
                            {
                                forwardDirection = true; // forward from even to odd position
                                int firstIntersectionId = intersectionId;
                                int secondIntersectionId = intersectionId + 1;
                                // check if segment start and and are inside the polygon
                                extendPolygonIfEndpointsOnEdge( numPoly ,firstIntersectionId, secondIntersectionId, forwardDirection);
                                intersectionId++;
                            }
                            else    // if intersection id is odd the segment inside the polygon is (id-1),(id)
                            {
                                forwardDirection = false;// backward from odd to even position
                                int firstIntersectionId =intersectionId-1;
                                int secondIntersectionId = intersectionId;
                                // check if segment start and and are inside the polygon
                                extendPolygonIfEndpointsOnEdge( numPoly ,firstIntersectionId, secondIntersectionId, forwardDirection);
                                intersectionId--;
                             }
                             //end

                            id = _intersectionIdToSegmentId[intersectionId];
                            // se il punto d'intersezione d'arrivo != seguente vertice cioè se non cade sul vertice succesivo
                            // se i due punti sono uguali non o aggiungo perche lo metto al prossimo ciclo e verrebbe un "doppione"
                            if (_intersectionVertices[intersectionId] != vertices[_polygon.nextVertexId(id)])
                            {
                                // significa che c è un vertice isolato per l intersezione in cui è impossibile passare ed allora lo settiamo
                                // true ed invece esploriamo l intersezione sul vertice (aggiunta ad inizio ciclo) in quanto hanno le stesse coordinate
                                // per saperlo bisogna vedere se i due punti di intersezione consecutivi sono lo stesso e quindi coincidente con il vertice
                                if ( (forwardDirection && _intersectionVertices[intersectionId] == _intersectionVertices[intersectionId - 1])
                                     || (!forwardDirection && _intersectionVertices[intersectionId] == _intersectionVertices[intersectionId + 1]))
                                    _foundVertex[id] = true;
                                else
                                {
                                    _newPolygons[numPoly].appendVertex(_intersectionVertices[intersectionId]);
                                    _extendedNewPolygons[numPoly].appendVertex(_intersectionVertices[intersectionId]);
                                }
                            }

                            id = _polygon.nextVertexId(id);
                        }
                    } while (id != n);

                    // with each cycle a sub-polygon have been discovered
                    numPoly++;
                }
            }//end else
    }
    // Fills _edges attribute of newPolygons costructed by cutting as opposed to those constructed by the constructor
    for (unsigned int j = 0; j < _newPolygons.size(); j++)
    {
        _newPolygons[j].buildUpPolygonEdges();
        _extendedNewPolygons[j].buildUpPolygonEdges();
    }

    return _newPolygons;


}


const vector<Point> &IntersectorPolygonLine::findNewPoints()
{
    // adds start and end of the segment if they are inside the polygon
    if(_startFound == true )
    {
        _newPoints.push_back(_line.getStart());
    }
    if(_endFound == true)
    {
        _newPoints.push_back(_line.getEnd());
    }

    //loops through _intersectionVertices and adds the ones that don't fall in a vertex since they are not newPoints
    for(unsigned int k = 0; k < _intersectionVertices.size(); k++)
    {
       int segmentPosition = _intersectionIdToSegmentId[k];
       const Point&  segmentStartPoint = _polygon.getEdges()[segmentPosition].getStart();
       const Point&  segmentEndPoint = _polygon.getEdges()[segmentPosition].getEnd();
       if (_intersectionVertices[k] != segmentStartPoint && _intersectionVertices[k] != segmentEndPoint)
            _newPoints.push_back(_intersectionVertices[k]);
    };

    return _newPoints;
}

// per cercare la tipologia di intersezione su vertice
// l output di acos è [0, pi]
bool IntersectorPolygonLine::checkInConicCombination(const Vector2d& line, const Vector2d& v1, const Vector2d& v2, int& flag) const
{
    const Vector2d nline = line.normalized();
    const Vector2d nv1 = v1.normalized();
    const Vector2d nv2 = v2.normalized();

    // calcolare la bisettrice
    Vector2d bisector = nv1 + nv2;
    bisector = bisector.normalized();

    const double theta = acos(bisector.dot(nv1));
    const double alfa  = acos(bisector.dot(nline));

    // means bisector is perpendicular to the edge, so the vertex has been added to create a conforming mesh
    // in this case there is a single intersection point
    if ((abs(theta - M_PI/2)) < INTERSECTION_TOLERANCE)
    {
        flag = 0;
        return false;
    }

    // double intersection point
    if (alfa < theta)
    {
        flag = 1;
        return true;
    }

    // double intersection point but in reversed order
    else if (alfa > M_PI/2 && (M_PI - alfa) < theta)
    {
        flag = -1;
        return true;
    }

    flag = 0;
    return false;
}

void IntersectorPolygonLine::extendPolygonIfEndpointsOnEdge(int& numPoly, const int &firstIntersectionId, const int &secondIntersectionId, const bool &forwardDirection)
{

        if (  _mapIntersectionIdToParametricCoordinate[firstIntersectionId] < 0
              && _mapIntersectionIdToParametricCoordinate[secondIntersectionId]  > 0
              && _mapIntersectionIdToParametricCoordinate[secondIntersectionId]  < 1)
        {

               _extendedNewPolygons[numPoly].appendVertex(_line.getStart());
               _startFound = true;
        }

        else if (  _mapIntersectionIdToParametricCoordinate[firstIntersectionId]  < 0
                   && _mapIntersectionIdToParametricCoordinate[secondIntersectionId]  > 1)//A e B
        {
                if(forwardDirection == true){
                   _extendedNewPolygons[numPoly].appendVertex(_line.getStart());
                   _startFound = true;
                   _extendedNewPolygons[numPoly].appendVertex(_line.getEnd());
                   _endFound = true;
                }
                else
                {
                    _extendedNewPolygons[numPoly].appendVertex(_line.getEnd());
                    _endFound = true;
                    _extendedNewPolygons[numPoly].appendVertex(_line.getStart());
                    _startFound = true;
                }
        }
        else if (  _mapIntersectionIdToParametricCoordinate[firstIntersectionId]  > 0
                   && _mapIntersectionIdToParametricCoordinate[firstIntersectionId]  < 1
                   && _mapIntersectionIdToParametricCoordinate[secondIntersectionId]  > 1)
        {
               _extendedNewPolygons[numPoly].appendVertex(_line.getEnd());
               _endFound = true;
        }
        else if ( _mapIntersectionIdToParametricCoordinate[firstIntersectionId ]  > 0
             && _mapIntersectionIdToParametricCoordinate[firstIntersectionId ]  < 1
             && _mapIntersectionIdToParametricCoordinate[secondIntersectionId]  < 0)
        {

               _extendedNewPolygons[numPoly].appendVertex(_line.getStart());
               _startFound = true;

        }
        else if (  _mapIntersectionIdToParametricCoordinate[firstIntersectionId]  > 1
                   && _mapIntersectionIdToParametricCoordinate[secondIntersectionId]  < 0)//B e A
        {

            if(forwardDirection == true){
                 _extendedNewPolygons[numPoly].appendVertex(_line.getEnd());
                 _endFound = true;
                 _extendedNewPolygons[numPoly].appendVertex(_line.getStart());
                 _startFound = true;
            }
            else
            {
                _extendedNewPolygons[numPoly].appendVertex(_line.getStart());
                _startFound = true;
                _extendedNewPolygons[numPoly].appendVertex(_line.getEnd());
                _endFound = true;
            }
        }
        else if (  _mapIntersectionIdToParametricCoordinate[firstIntersectionId]  > 1
                   && _mapIntersectionIdToParametricCoordinate[secondIntersectionId]  < 1
                   && _mapIntersectionIdToParametricCoordinate[secondIntersectionId]  > 0)
        {
               _extendedNewPolygons[numPoly].appendVertex(_line.getEnd());
               _endFound = true;
        }
}


}

