#ifndef REFERENCEELEMENT_H
#define REFERENCEELEMENT_H

#include <Polygon.hpp>
#include <vector>

namespace MeshNamespace { class Mesh; }
namespace ReferenceElementNamespace {

  class IReferenceElement {
    public:
      virtual  void computeBoundingBox(Polygon& polygon) = 0;
      virtual  void computeReferenceElement(Polygon& polygon) = 0;
      virtual const vector<Point>& getBoundingBoxVertices() const = 0;
      virtual const vector<Polygon>& getReferenceElementPolygons() const = 0;
      virtual  const Point& getBoundingBoxVertexAtPosition(unsigned int& i)  = 0;

      virtual void findBoundaryVertices() = 0;
      virtual const map<double, Point>& getMapSouthXCoordinates() const = 0;
      virtual const map<double, Point>& getMapNorthXCoordinates() const = 0;
      virtual const map<double, Point>& getMapEastYCoordinates() const = 0;
      virtual const map<double, Point>& getMapWestYCoordinates() const = 0;

      virtual void makeConforming() = 0;
      virtual const vector<Polygon>& getConformingReferenceElementPolygons() const = 0;
  };


  class ReferenceElement : public IReferenceElement
  {
     private:

      vector<Point> _boundingBoxVertices;
      vector<Polygon> _referenceElementPolygons;
      vector<Polygon> _conformingReferenceElementPolygons;
      Polygon _boundingBox;

      map<double, Point> _mapSouthXCoordinates;
      map<double, Point> _mapNorthXCoordinates;
      map<double, Point> _mapWestYCoordinates;
      map<double, Point> _mapEastYCoordinates;
      double _minX;
      double _minY;
      double _maxX;
      double _maxY;
      friend class MeshNamespace::Mesh;

     public:
      ReferenceElement();

      void computeReferenceElement(Polygon& polygon);
      const vector<Polygon>& getReferenceElementPolygons() const {return _referenceElementPolygons;}
      void showReferenceElement(const string filePath = "showReferenceElement.m");

      void computeBoundingBox(Polygon& polygon);
      const vector<Point>& getBoundingBoxVertices() const {return _boundingBoxVertices;}
      const Point& getBoundingBoxVertexAtPosition(unsigned int& i) {return _boundingBoxVertices[i];}
      const Polygon& getBoundingBox(){return _boundingBox;}

      void findBoundaryVertices();
      const map<double, Point>& getMapSouthXCoordinates() const {return _mapSouthXCoordinates;}
      const map<double, Point>& getMapNorthXCoordinates() const {return _mapNorthXCoordinates;}
      const map<double, Point>& getMapEastYCoordinates() const {return _mapEastYCoordinates;}
      const map<double, Point>& getMapWestYCoordinates() const {return _mapWestYCoordinates;}

      void makeConforming();
      const vector<Polygon>& getConformingReferenceElementPolygons() const {return _conformingReferenceElementPolygons;}
  };
}

#endif // REFERENCEELEMENT_H
