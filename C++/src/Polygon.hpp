#ifndef POLYGON_H
#define POLYGON_H

#include "Segment.hpp"
#include <vector>

using namespace std;

  class IPolygon
  {
    public:
      virtual unsigned int getNumberVertices()const = 0;
      virtual const vector<Point>& getVertices() const = 0;
      virtual void setVertexAtPosition(const Point& vertex, const int& position) = 0;
      virtual void appendVertex( const Point& vertex)=0;
      virtual void insertVertexAtPosition(const Point& vertex, const int& position) = 0;
      virtual const Point& getVertexAtPosition(const int& position) const = 0;
      virtual int nextVertexId(unsigned int id) const = 0;
      virtual const Point& getLastVertex() const = 0;

      virtual const vector<Segment>& getEdges() const = 0;
      virtual void buildUpPolygonEdges() = 0;

      virtual void setVertexLabelAtPosition(const int& position, int label) = 0;
      virtual int getVertexLabelAtPosition(const int& position) const = 0;
      virtual void setVertexLabels( const vector<unsigned int> &polygonVertices) = 0;
      virtual void setDefaultVertexLabels() = 0;

      virtual double ComputeArea() const = 0;

      virtual  bool pointInPolygon(const Point& point) = 0;

      virtual int isPolygonOnTheRightSide(const Segment& line) const = 0;
  };


  class Polygon : public IPolygon
  {
    private:
      unsigned int _numberVertices;
      vector<Point> _vertices;
      vector<Segment> _edges;

    public:
      Polygon();
      Polygon(const vector<Point>& vertices);

      unsigned int getNumberVertices()const { return _numberVertices;}
      const vector<Point>& getVertices() const {return _vertices;}
      void setVertexAtPosition(const Point& vertex, const int& position);
      void appendVertex( const Point& vertex);
      void insertVertexAtPosition(const Point& vertex, const int& position);
      const Point& getVertexAtPosition(const int& position) const{return _vertices[position];}
      int nextVertexId(unsigned int id) const;
      const Point& getLastVertex() const {return _vertices[_numberVertices - 1];};

      const vector<Segment>& getEdges() const {return _edges;}   
      void buildUpPolygonEdges();   // useful when polygons are created by appending vertices

      void setVertexLabelAtPosition(const int& position, int label);
      int getVertexLabelAtPosition(const int& position) const { return _vertices[position].getPointLabel();}
      void setVertexLabels( const vector<unsigned int> &polygonVertices);
      void setDefaultVertexLabels();

      double ComputeArea() const ;

      bool pointInPolygon(const Point& point);
      int isPolygonOnTheRightSide(const Segment& line) const;

      Polygon& operator = (const Polygon& polygon);
  };


#endif
