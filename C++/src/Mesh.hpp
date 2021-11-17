#ifndef MESHCLASS_H
#define MESHCLASS_H

#include<ReferenceElement.hpp>

using namespace ReferenceElementNamespace;

namespace MeshNamespace {

  class IMesh {
    public:
      virtual void createMesh() = 0;
      virtual ReferenceElement TranslateConformingReferenceElement(double xTranslation, double yTranslation ) = 0;
      virtual Polygon TranslatePolygon(const Polygon& polygon, double xTranslation, double yTranslation) = 0;
      virtual void setRectangularDomain(const double& length, const double& height) = 0;
      virtual void setConvexDomain(const Polygon & convexDomain) = 0;
      virtual bool referenceElementInConvexDomain(ReferenceElement& referenceElement ) = 0;
      virtual void cutAndDiscardPolygonsOnRightSide( ReferenceElement& referenceElement, Segment& line ) = 0;

      virtual double &getBoundingBoxLength() = 0;
      virtual double &getBoundingBoxHeight() = 0;
      virtual unsigned int &getMaxNumRefElementsPerRow() = 0;
      virtual unsigned int &getMaxNumRefElementsPerColumn() = 0;
      virtual const Polygon &getDomainBoundingBox() = 0;
      virtual const Polygon& getDomain() const = 0;
      virtual const vector<ReferenceElement>& getMeshCells() const  = 0;
      virtual const Polygon& getReferenceElementBoundingBox() = 0;
      virtual double& getDomainBoundingBoxLength() = 0;
      virtual double& getDomainBoundingBoxHeight() = 0;
      virtual ReferenceElement& getReferenceElement() = 0;

      virtual void showMesh(const string filePath = "showMesh.m") = 0;
  };

  class Mesh : public IMesh
  {
    private:
      vector<ReferenceElement> _meshCells; //output

      ReferenceElement _referenceElement;  //it's conforming

      vector<Polygon> _conformingReferenceElementPolygons;
      Polygon _referenceElementBoundingBox;
      double _boundingBoxLength;
      double _boundingBoxHeight;

      Polygon _domain;
      Polygon _domainBoundingBox;
      unsigned int _maxNumRefElementsPerRow;
      unsigned int _maxNumRefElementsPerColumn;
      double _domainBoundingBoxLength;
      double _domainBoundingBoxHeight;

    public:
      Mesh();
      Mesh(Polygon& referencePolygon);

      void createMesh();
      ReferenceElement TranslateConformingReferenceElement(double xTranslation, double yTranslation ) ;
      Polygon TranslatePolygon(const Polygon& polygon, double xTranslation, double yTranslation) ;
      void setRectangularDomain(const double& length, const double& height);
      void setConvexDomain(const Polygon & convexDomain);
      bool referenceElementInConvexDomain(ReferenceElement& referenceElement );
      void cutAndDiscardPolygonsOnRightSide( ReferenceElement& referenceElement, Segment& line );

      double &getBoundingBoxLength(){return _boundingBoxLength;}
      double &getBoundingBoxHeight(){return _boundingBoxHeight;}
      unsigned int &getMaxNumRefElementsPerRow(){return _maxNumRefElementsPerRow;}
      unsigned int &getMaxNumRefElementsPerColumn(){return _maxNumRefElementsPerColumn;}
      const Polygon &getDomainBoundingBox(){return _domainBoundingBox; }
      const Polygon& getDomain() const{return _domain;}
      const vector<ReferenceElement>& getMeshCells() const {return _meshCells;}
      const Polygon& getReferenceElementBoundingBox(){ return _referenceElementBoundingBox;}
      double& getDomainBoundingBoxLength(){ return _domainBoundingBoxLength;}
      double& getDomainBoundingBoxHeight(){ return _domainBoundingBoxHeight;}
      ReferenceElement& getReferenceElement(){ return _referenceElement;}

      void showMesh(const string filePath = "showMesh.m");

  };
}

#endif // MESHCLASS_H
