#include "Mesh.hpp"
#include "Polygon.hpp"
#include "IntersectorPolygonLine.hpp"
#include <fstream>

using namespace ReferenceElementNamespace;
using namespace IntersectorPolygonLineNamespace;

namespace MeshNamespace {

Mesh::Mesh(){

    _boundingBoxLength = 0;
    _boundingBoxHeight = 0;
}

//for generic convex domain
Mesh::Mesh(Polygon& referencePolygon)
{
    _referenceElement.computeBoundingBox(referencePolygon);
    _referenceElement.computeReferenceElement(referencePolygon);

    _referenceElementBoundingBox = _referenceElement._boundingBox;

    _referenceElement.findBoundaryVertices();
    _referenceElement.makeConforming();
    _conformingReferenceElementPolygons = _referenceElement.getConformingReferenceElementPolygons();

    _boundingBoxLength = _referenceElementBoundingBox.getEdges()[0].getTangent().norm();
    _boundingBoxHeight = _referenceElementBoundingBox.getEdges()[1].getTangent().norm();
}

void Mesh::createMesh()
{
    //Before calling this function a Mesh Object should be constructed and a domain should be set

    //place referenceElement at (0,0)
    double xTranslation = -_referenceElementBoundingBox.getVertices()[0].getCoordinates().x();
    double yTranslation = -_referenceElementBoundingBox.getVertices()[0].getCoordinates().y();
    _referenceElement = TranslateConformingReferenceElement(xTranslation, yTranslation);
    _referenceElementBoundingBox = _referenceElement._boundingBox;


  for(unsigned int row = 0; row < _maxNumRefElementsPerColumn; row++)
  {
      for(unsigned int column = 0; column < _maxNumRefElementsPerRow; column++)//columns of the row
      {
           //translate the ConformingReferenceElement in multiples of the bounding box's dimensions
           ReferenceElement translatedReferenceElement = TranslateConformingReferenceElement(_boundingBoxLength*column, _boundingBoxHeight*row);

           if(referenceElementInConvexDomain(translatedReferenceElement)) // If the translated reference Element is inside the domain
           {
              _meshCells.push_back(translatedReferenceElement); //just push it
           }
           else
            {
               //check if any edge of the domain intersects the bounding box of the translated reference element. If there is no intersection
               //the referenceElement is outside so it is not added to the matrix of ReferenceElements. If there is an intersection, the translated
               //reference element is cutted and a new one is built with the polygons that are inside the domain

               bool intersectionWithDomain = false;
               for( unsigned int i = 0; i < _domain.getNumberVertices(); i++) //fixes a domain edge
               {
                   Segment line = _domain.getEdges()[i];
                   Intersector1D1D intersector1d1d;
                   const vector<Segment> edges = translatedReferenceElement._boundingBox.getEdges();
                   intersector1d1d.SetFirstSegment(line.getStart().getCoordinates(), line.getEnd().getCoordinates());

                   for (unsigned int l = 0; l < 4; l++)//edges of ReferenceElement's Bounding Box
                   {

                       intersector1d1d.SetSecondSegment(edges[l].getStart().getCoordinates(), edges[l].getEnd().getCoordinates());

                       if(intersector1d1d.ComputeIntersection()) //If there is intersection
                       {
                           //if the intersection is OnSegment with rispect to the domain
                           if (intersector1d1d.TypeIntersection() == Intersector1D1D::IntersectionOnSegment)
                           {
                               intersectionWithDomain = true;
                               // We need this flag so that in the push back below
                               //the reference Element is not added if it falls outside the domain
                               cutAndDiscardPolygonsOnRightSide(translatedReferenceElement, line);//this modifies the input translatedReferenceElement
                               break;
                            }
                       }

                    }//end for //break
               }//end for : loop over domain edges

               if (intersectionWithDomain)
                   _meshCells.push_back(translatedReferenceElement); // add the element after it has been cutted one or more times

           }//end else

      }//end for: column loop
  }//end for : row loop

}

ReferenceElement Mesh::TranslateConformingReferenceElement( double xTranslation, double yTranslation )
{
    vector<Polygon> translatedConformingPolygons;
    vector<Polygon> conformingPolygons = _referenceElement.getConformingReferenceElementPolygons();
    for (unsigned int i = 0; i < conformingPolygons.size(); i++)
    {
        Polygon translatedPolygon = TranslatePolygon(conformingPolygons[i], xTranslation, yTranslation);
        translatedConformingPolygons.push_back(translatedPolygon);
    }

    Polygon translatedBoundingBox = TranslatePolygon(_referenceElementBoundingBox, xTranslation, yTranslation);
    //now that we have a new vector of polygons and the bounding box  in the new Position
    //a new referenceElement is created to group all that data

    ReferenceElement translatedReferenceElement;
    translatedReferenceElement._conformingReferenceElementPolygons = translatedConformingPolygons;
    translatedReferenceElement._boundingBox = translatedBoundingBox;
    translatedReferenceElement._boundingBoxVertices = translatedBoundingBox.getVertices();

return translatedReferenceElement;

}

Polygon Mesh::TranslatePolygon(const Polygon& polygon, double xTranslation, double yTranslation)
{
    Polygon translatedPolygon = Polygon();

    const vector<Point>& initialVertices = polygon.getVertices();
    for (vector<Point>::const_iterator it = initialVertices.begin(); it != initialVertices.end(); it++)
    {
        Point initialVertex = Point(it->getCoordinates());
        Point translation =  Point(xTranslation, yTranslation);
        Point TranslatedVertex = initialVertex + translation;
        translatedPolygon.appendVertex(TranslatedVertex);
    }
    translatedPolygon.buildUpPolygonEdges(); // this fixes the edges, since the appendVertices only modifies the  polygon's vertices

  return translatedPolygon;
}

void Mesh::setRectangularDomain(const double& domainLength, const double& domainHeight)
{
    vector<Point> rectangleVertices;
    rectangleVertices.resize(4);
    rectangleVertices[0] = Point(0, 0);
    rectangleVertices[1] = Point(domainLength, 0);
    rectangleVertices[2] = Point(domainLength, domainHeight);
    rectangleVertices[3] = Point(0, domainHeight);
    _domain = Polygon(rectangleVertices);
    _domainBoundingBox = _domain;
    _domainBoundingBoxLength = domainLength;
    _domainBoundingBoxHeight = domainHeight;

    _maxNumRefElementsPerRow = (unsigned int)ceil((domainLength/_boundingBoxLength));
    _maxNumRefElementsPerColumn = (unsigned int)ceil((domainHeight/_boundingBoxHeight));
    _meshCells.reserve(_maxNumRefElementsPerColumn*_maxNumRefElementsPerRow);
}

void Mesh::setConvexDomain(const Polygon & convexDomain)
{   //create a Mesh object with arguments before setting the domain

    if(  _boundingBoxLength == 0 || _boundingBoxHeight == 0)
        throw runtime_error("first create a Mesh object with a polygon");

    _domain = convexDomain;
    ReferenceElement ref;
    ref.computeBoundingBox(_domain);
    _domainBoundingBox = ref.getBoundingBox();
    _domainBoundingBoxLength = _domainBoundingBox.getEdges()[0].getTangent().norm();
    _domainBoundingBoxHeight = _domainBoundingBox.getEdges()[1].getTangent().norm();

    //the next two attributes allow to know how many times  the original referenceElement should be translated rightwards and upwards
    _maxNumRefElementsPerRow = (unsigned int)ceil((_domainBoundingBoxLength/_boundingBoxLength));
    _maxNumRefElementsPerColumn = (unsigned int)ceil((_domainBoundingBoxHeight/_boundingBoxHeight));

    _meshCells.reserve(_maxNumRefElementsPerColumn*_maxNumRefElementsPerRow);
}



bool Mesh::referenceElementInConvexDomain(ReferenceElement& referenceElement)
{
    unsigned int i;
    bool flag = 1; // by default the referenceElemnt is in the domain

    for(i = 0; i < 4 && flag == 1; i++) //loops over the four vertices of the polygon's bounding box
    {
        Point BBvertex = referenceElement.getBoundingBoxVertexAtPosition(i);
        bool flag2 = _domain.pointInPolygon(BBvertex);
        if(flag2 == 0) // if one of the vertices of the polygons's bounding box is not in the domain
            flag = 0;   // it means the reference element is not in the domain, flag is set to 0 and the following for cycles are interrupted
    }

    return flag;
}

void Mesh::cutAndDiscardPolygonsOnRightSide( ReferenceElement& referenceElement, Segment& line)
{
    //This method creates a new vector of polygons called newVectorOfPolygons in which to store each of the new Polygons obtained cutting
    //the vector of polygons referenceElement with the segment line
    //at the end the vector<Polygon> _conformingReferenceElementPolygons is updated with the new Polygons.

    vector<Polygon> newVectorOfPolygons;

    for (unsigned int i = 0; i < referenceElement.getConformingReferenceElementPolygons().size(); i++)
    {
        Polygon &polygon = referenceElement._conformingReferenceElementPolygons[i];
        //if polygon is on the rigth side, skip the polygon discarding it
        if(polygon.isPolygonOnTheRightSide(line) == 1)
            continue;
        //If polygon is on the left side, just add the whole polygon, no need to cut
        else if(polygon.isPolygonOnTheRightSide(line) == -1)
        {
            newVectorOfPolygons.push_back(polygon);
        }
        // If polygon is  not on the rigth nor on the left there is intersection
        else
        {
            Intersector1D1D intersector1d1d;
            IntersectorPolygonLine intersector(intersector1d1d, polygon, line);                       
            intersector.findIntersectionVertices();
            vector<Polygon> newPolygons = intersector.findPolygons();

            for (unsigned int j = 0; j < newPolygons.size(); j++)
              {
                  //if the new polygon is on the left side, add it
                  if(newPolygons[j].isPolygonOnTheRightSide(line) == -1)
                     newVectorOfPolygons.push_back(newPolygons[j]);
              }
        }

    }

    referenceElement._conformingReferenceElementPolygons.clear();
    referenceElement._conformingReferenceElementPolygons = newVectorOfPolygons;//referenceElement is updated with the new polygons
}

void Mesh::showMesh(const string filePath)
{
    if (_meshCells.empty())
        throw runtime_error("First you need to create mesh");

    ofstream of;
    of.open (filePath);

    of << "width = 1.0;" << endl
       << "figure;" << endl
       << "hold on;" << endl
       << "axis off;" << endl << endl;

    for (unsigned int i = 0; i < _meshCells.size(); i++)
    {
        const vector<Polygon> conformingReferenceElementPolygons = _meshCells[i].getConformingReferenceElementPolygons();

        int number = conformingReferenceElementPolygons.size();
        of << "newColors = lines(" << number << ");" << endl;
        of << "colororder(newColors)" << endl << endl;

        for (int n = 0; n < number; n++)
        {
            of << "points" << number*i+n+1 << " = [" << endl;
            const vector<Point>& points = conformingReferenceElementPolygons[n].getVertices();
            for (unsigned int i = 0; i < conformingReferenceElementPolygons[n].getNumberVertices(); i++)
                of << "\t" << points[i].getCoordinates()[0] << ", " << points[i].getCoordinates()[1] << endl;

            of << "];" << endl;
            of << "polygon" << number*i+n+1 << " = polyshape(points" << number*i+n+1 << ");" << endl
               << "plot(polygon" << number*i+n+1 << ", 'LineWidth', width);" << endl << endl;
        }
    }

    of << "hold off;" << endl;
    of.close();
}

}
