#include "ReferenceElement.hpp"
#include "fstream"

namespace ReferenceElementNamespace {

  ReferenceElement::ReferenceElement()
  {
    _boundingBoxVertices.resize(4);
  }


  void ReferenceElement::computeBoundingBox(Polygon& polygon)
  {
    unsigned int n ;
    unsigned int numberVertices;
    double minX, minY, maxX, maxY;
    //initializing variables to a firts value to avoid an iteration in the for cicle
    minX = polygon.getVertexAtPosition(0).getCoordinates().x();
    maxX = polygon.getVertexAtPosition(0).getCoordinates().x();
    minY = polygon.getVertexAtPosition(0).getCoordinates().y();
    maxY = polygon.getVertexAtPosition(0).getCoordinates().y();

    numberVertices = polygon.getNumberVertices();

    //looking for the extremes in x and y to compute the bounding box
    for(n = 1; n < numberVertices; n++ )
    {
        if (polygon.getVertexAtPosition(n).getCoordinates().x() < minX)
            minX = polygon.getVertexAtPosition(n).getCoordinates().x();

        if (polygon.getVertexAtPosition(n).getCoordinates().x() > maxX)
            maxX = polygon.getVertexAtPosition(n).getCoordinates().x();

        if (polygon.getVertexAtPosition(n).getCoordinates().y() < minY)
            minY = polygon.getVertexAtPosition(n).getCoordinates().y();

        if (polygon.getVertexAtPosition(n).getCoordinates().y() > maxY)
            maxY = polygon.getVertexAtPosition(n).getCoordinates().y();

         }

    //initializing attributes
    _boundingBoxVertices[0] = Point(Vector2d(minX, minY));
    _boundingBoxVertices[1] = Point(Vector2d(maxX, minY));
    _boundingBoxVertices[2] = Point(Vector2d(maxX, maxY));
    _boundingBoxVertices[3] = Point(Vector2d(minX, maxY));
    _minX = minX;
    _minY = minY;
    _maxX = maxX;
    _maxY = maxY;
    _boundingBox = Polygon(_boundingBoxVertices);
  }

    void  ReferenceElement::computeReferenceElement(Polygon& polygon)
  {
      unsigned int i, n, numberVertices;
      vector<Polygon> referenceElement;
      vector<Point> vertices;
      bool temp = 0;
      double minX, minY, maxX, maxY;

      numberVertices = polygon.getNumberVertices();
      minX = _boundingBoxVertices[0].getCoordinates().x();
      minY = _boundingBoxVertices[0].getCoordinates().y();
      maxX = _boundingBoxVertices[2].getCoordinates().x();
      maxY = _boundingBoxVertices[2].getCoordinates().y();

      //push_back of the original polygon in the vector of polygons inside the bounding box
      _referenceElementPolygons.push_back(polygon);

      //looking for the first vertex of the initial polygon that lies on the lower edge of the bounding box and to start the iteration
      for(n = 0; n < numberVertices && temp == 0; n++)
      {
          if(polygon.getVertexAtPosition(n).getCoordinates().y() == minY)
          {
              temp = 1;
              vertices.push_back(polygon.getVertexAtPosition(n));
          }
      }

      //for cicle on all polygon vertices
      for(i = 0; i < numberVertices; i++)
      {
          double x = polygon.getVertexAtPosition((n + i) % numberVertices).getCoordinates().x();
          double y = polygon.getVertexAtPosition((n + i) % numberVertices).getCoordinates().y();

          //controlling if vertices[0](it has intersection with one of the edges) and the next vertex of the polygon lie on the same edge to not form a new polygon that is a segment
          if ((y == minY) && (polygon.getVertexAtPosition((n + i - 1) % numberVertices).getCoordinates().y() == minY))
             vertices[0] = polygon.getVertexAtPosition((n +i) % numberVertices);

          //controlling if vertices[0](it has intersection with one of the edges) and the next vertex of the polygon lie on the same edge to not form a new polygon that is a segment
          else if ((x == maxX) && (polygon.getVertexAtPosition((n + i - 1) % numberVertices).getCoordinates().x() == maxX))
             vertices[0] = polygon.getVertexAtPosition((n +i) % numberVertices);

          //controlling if vertices[0](it has intersection with one of the edges) and the next vertex of the polygon lie on the same edge to not form a new polygon that is a segment
          else if ((y == maxY) && (polygon.getVertexAtPosition((n + i - 1) % numberVertices).getCoordinates().y() == maxY))
             vertices[0] = polygon.getVertexAtPosition((n +i) % numberVertices);

          //controlling if vertices[0](it has intersection with one of the edges) and the next vertex of the polygon lie on the same edge to not form a new polygon that is a segment
          else if ((x == minX) && (polygon.getVertexAtPosition((n + i - 1) % numberVertices).getCoordinates().x() == minX))
             vertices[0] = polygon.getVertexAtPosition((n +i) % numberVertices);

          //if the vertex analyzed doesn'lie on an edge of the bounding box, it will be a vertex of the new polygon
          else if((x != maxX) && (x != minX)  && (y != minY) && (y != maxY))
             vertices.push_back(polygon.getVertexAtPosition((n + i) % numberVertices));

          //if the vertex analyzed lies on the bottom edge of the bounding box
          else if(y == minY)
          {
              //if vertices[0] lies on the lower edge we immediately form a new polygon
              if (vertices[0].getCoordinates().y() == minY)
              {
                  vertices.push_back(polygon.getVertexAtPosition((n + i) % numberVertices));
              }

              //if vertices[0] lies on the left edge of the bounding box we control if we must add the first bounding box vertex
              else if (vertices[0].getCoordinates().x() == minX)
              {
                  vertices.push_back(polygon.getVertexAtPosition((n + i) % numberVertices));

                  //controlling if the vertex analyzed is different from the first bounding box vertex in order to add the bounding box vertex in the new polygon
                  if (polygon.getVertexAtPosition((n + i) % numberVertices) != _boundingBoxVertices[0])
                      vertices.push_back(_boundingBoxVertices[0]);

              }

              //if vertices[0] lies on the upper edge of the bounding box we control if we must add the first or the fourth bounding box vertex
              else if (vertices[0].getCoordinates().y() == maxY)
              {
                  vertices.push_back(polygon.getVertexAtPosition((n + i) % numberVertices));

                  //controlling if the analyzed vertex is different form the first bounding box vertex in order to add the bounding box vertex to the new polygon
                //  if(polygon.getVertexAtPosition((n + i) % numberVertices) != _boundingBoxVertices[0]) // forse da togliere
                     //   vertices.push_back(_boundingBoxVertices[0]);

                  //controlling if the analyzed vertex is different form the third bounding box vertex in order to add the bounding box vertex to the new polygon
                  // we add only the third vertex because the only possible case is that in which vertices[0] = boundingBoxVertices[0]
                  if(vertices[0] != _boundingBoxVertices[3])
                        vertices.push_back(_boundingBoxVertices[3]);

              }


            reverse(vertices.begin(), vertices.end());  //reversing vector to have anticlockwise order in the position of the vertices vector, according to the indices

            //adding the new polygon
            _referenceElementPolygons.push_back(Polygon(vertices));
            vertices.clear();
            //adding the last vertex analyzed, in fact tha last vertex may be  the vertex of the next polygon
            vertices.push_back(polygon.getVertexAtPosition((n + i) % numberVertices));

          }

          //if the vertex analyzed lies on the right edge of the bounding box
          else if (x == maxX)
          {
              //if vertices[0] lies on the same edge we immediately add a new polygon
              if (vertices[0].getCoordinates().x() == maxX)
              {
                  vertices.push_back(polygon.getVertexAtPosition((n + i) % numberVertices));

              }

              //if vertices[0] lies on the lower edge we control if we must add the second bounding box vertex
              else if(vertices[0].getCoordinates().y() == minY)
              {
                  vertices.push_back(polygon.getVertexAtPosition((n + i) % numberVertices));

                  //if the analyzed vertex is different form the first bounding box vertex
                  if (polygon.getVertexAtPosition((n + i) % numberVertices) != _boundingBoxVertices[1])
                       vertices.push_back(_boundingBoxVertices[1]);
              }

              //reversing vector to have anticlockwise order in the position of the vertices vector, according to the indices
              reverse(vertices.begin(), vertices.end());

              _referenceElementPolygons.push_back(Polygon(vertices));
              vertices.clear();
              vertices.push_back(polygon.getVertexAtPosition((n + i) % numberVertices));

          }

          //if the analyzed vertex lies on the upper edge of the bounding box
          else if (y == maxY)
          {
             //if vertices[0] lies on the same edge we immediately add a new polygon
             if (vertices[0].getCoordinates().y() == maxY)
             {
                 vertices.push_back(polygon.getVertexAtPosition((n + i) % numberVertices));

             }

            //if vertices[0] lies on the right edge of the bounding box
             else if (vertices[0].getCoordinates().x() == maxX)
             {
                 vertices.push_back(polygon.getVertexAtPosition((n + i) % numberVertices));

                 //if the analyzed vertex is different from the third bounding box vertex
                 if (polygon.getVertexAtPosition((n + i) % numberVertices) != _boundingBoxVertices[2])
                     vertices.push_back(_boundingBoxVertices[2]);

             }

             //reversing vector to have anticlockwise order in the position of the vertices vector, according to the indices
             reverse(vertices.begin(), vertices.end());
             _referenceElementPolygons.push_back(Polygon(vertices));
             vertices.clear();
             vertices.push_back(polygon.getVertexAtPosition((n + i) % numberVertices));
          }

          //if the analyzed vertex lies on the left edge
          else if (x == minX)
          {
              //if vertices[0] lies on the same edge we immediately add a new polygon
              if ( vertices[0].getCoordinates().x() == minX)
              {
                  vertices.push_back(polygon.getVertexAtPosition((n + i) % numberVertices));
              }

              //if vertices[0] lies on the upper edge of the bounding box
              else if (vertices[0].getCoordinates().y() == maxY)
              {
                  vertices.push_back(polygon.getVertexAtPosition((n + i) % numberVertices));
                  //if the analyzed vertex is different from the fourth bounding box
                  if (polygon.getVertexAtPosition((n + i) % numberVertices) != _boundingBoxVertices[3])
                       vertices.push_back(_boundingBoxVertices[3]);
              }

              //reversing vector to have anticlockwise order in the position of the vertices vector, according to the indices
              reverse(vertices.begin(), vertices.end());
              _referenceElementPolygons.push_back(Polygon(vertices));
              vertices.clear();
              vertices.push_back(polygon.getVertexAtPosition((n + i) % numberVertices));
          }

       }

    }

    void ReferenceElement::showReferenceElement(const string filePath)
    {
        ofstream of;
        of.open (filePath);

        of << "width = 1.0;" << endl
           << "figure;" << endl
           << "hold on;" << endl << endl;
        for (unsigned int n = 0; n < _referenceElementPolygons.size(); n++)
        {
            of << "points" << n+1 << " = [" << endl;
            const vector<Point>& points = _referenceElementPolygons[n].getVertices();
            for (unsigned int i = 0; i < _referenceElementPolygons[n].getNumberVertices(); i++)
                of << "\t" << points[i].getCoordinates()[0] << ", " << points[i].getCoordinates()[1] << endl;

            of << "];" << endl;
            of << "polygon" << n+1 << " = polyshape(points" << n+1 << ");" << endl
               << "plot(polygon" << n+1 << ", 'LineWidth', width);" << endl << endl;
        }
        of << "hold off;" << endl;

        of.close();
    }

    void ReferenceElement::findBoundaryVertices()
    {
        const vector<Point>& vertices = _referenceElementPolygons[0].getVertices();
        for(unsigned int i = 0; i < vertices.size(); i++)
        {

            if(vertices[i].getCoordinates().y() == _minY )
              {//If the point is on the south edge of the bounding box
                if(vertices[i] != _boundingBoxVertices[0] && vertices[i] != _boundingBoxVertices[1])
                   _mapSouthXCoordinates.insert(pair<double, Point>(vertices[i].getCoordinates().x(), vertices[i]));
              }
            else if(vertices[i].getCoordinates().y() == _maxY)
              {//If the point is on the north edge of the bounding box
                if(vertices[i] != _boundingBoxVertices[2] && vertices[i] != _boundingBoxVertices[3])
                   _mapNorthXCoordinates.insert(pair<double, Point>(vertices[i].getCoordinates().x(), vertices[i]));
              }
            else if(vertices[i].getCoordinates().x() == _maxX )
              {//If the point is on the east edge of the bounding box
                if(vertices[i] != _boundingBoxVertices[1] && vertices[i] != _boundingBoxVertices[2])
                   _mapEastYCoordinates.insert(pair<double, Point>(vertices[i].getCoordinates().y(), vertices[i]));
              }
            else if(vertices[i].getCoordinates().x() == _minX )
              {//If the point is on the west edge of the bounding box
                if(vertices[i] != _boundingBoxVertices[3] && vertices[i] != _boundingBoxVertices[0])
                   _mapWestYCoordinates.insert(pair<double, Point>(vertices[i].getCoordinates().y(), vertices[i]));
              }
        }
    }

    void ReferenceElement::makeConforming()
    {
      _conformingReferenceElementPolygons = _referenceElementPolygons;
      unsigned int numberNewPolygons = _referenceElementPolygons.size()-1;
      for(unsigned int p = 0; p <= numberNewPolygons; p++)
      {
          const vector<Point>& vertices = _referenceElementPolygons[p].getVertices();
          unsigned int numberVertices = _referenceElementPolygons[p].getNumberVertices();
          for(unsigned int i = 0; i < numberVertices; i++)
          {
               map<double, Point>::iterator it;

               //If the current polygons's edge is on the south edge of the bounding box(first if), I project onto it the non-corner Points
               //from the north edge of the box, meaning I insert the projected point as a new vertex on the current polygon
              if(vertices[i].getCoordinates().y() == _minY && vertices[(i + 1) % numberVertices].getCoordinates().y()  == _minY)
                {
                  for ( it = _mapNorthXCoordinates.begin(); it != _mapNorthXCoordinates.end(); it++)
                  {  //it->first is the x coordinate of the North x coordinates, so the projection is (it->first,_minY)
                     //ordering by x, the correct segment to project to is selected by the next if
                     if (vertices[i].getCoordinates().x() < it->first
                        && it->first < vertices[(i + 1) % numberVertices].getCoordinates().x())
                         _conformingReferenceElementPolygons[p].insertVertexAtPosition(Point(it->first,_minY), (i + 1)%numberVertices);
                  }
                }

              //If the edge is on the north edge of the bounding box, I project onto it the non-corner Points from the south edge of the box
              else if(vertices[i].getCoordinates().y() == _maxY && vertices[(i + 1) % numberVertices].getCoordinates().y()  == _maxY)
                {
                  for ( it = _mapSouthXCoordinates.begin(); it != _mapSouthXCoordinates.end(); it++)
                  {
                     if (vertices[i].getCoordinates().x() > it->first
                        && it->first > vertices[(i + 1) % numberVertices].getCoordinates().x())
                         _conformingReferenceElementPolygons[p].insertVertexAtPosition(Point(it->first,_maxY), (i + 1)%numberVertices);
                  }
                }

              //If the edge is on the east edge of the bounding box, I project onto it the non-corner Points from the west edge of the box
              else if(vertices[i].getCoordinates().x() == _maxX && vertices[(i + 1) % numberVertices].getCoordinates().x()  == _maxX)
                {
                  for ( it = _mapWestYCoordinates.begin(); it != _mapWestYCoordinates.end(); it++)
                  {
                     if (vertices[i].getCoordinates().y() < it->first
                        && it->first < vertices[(i + 1) % numberVertices].getCoordinates().y())
                         _conformingReferenceElementPolygons[p].insertVertexAtPosition(Point(_maxX, it->first), (i + 1)%numberVertices);
                  }
                }
              //If the edge is on the west edge of the bounding box, I project onto it the non-corner Points from the east edge of the box
               else if(vertices[i].getCoordinates().x() == _minX && vertices[(i + 1) % numberVertices].getCoordinates().x()  == _minX)
                {
                  for ( it = _mapEastYCoordinates.begin(); it != _mapEastYCoordinates.end(); it++)
                  {
                     if (vertices[i].getCoordinates().y() > it->first
                        && it->first > vertices[(i + 1) % numberVertices].getCoordinates().y())
                         _conformingReferenceElementPolygons[p].insertVertexAtPosition(Point(_minX, it->first), (i + 1)%numberVertices);
                  }
                }
            }
        }
    }
}
