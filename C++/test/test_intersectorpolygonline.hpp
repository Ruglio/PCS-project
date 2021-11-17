#ifndef __TEST_INTERSECTORPOLYGONLINECLASS_H
#define __TEST_INTERSECTORPOLYGONLINECLASS_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>

#include<iostream>
#include "IntersectorPolygonLine.hpp"
#include "Eigen"

using namespace IntersectorPolygonLineNamespace;
using namespace testing;
using namespace std;
using namespace Eigen;

namespace IntersectorPolygonLineTesting {

class MockSegment : public ISegment {
  public:
    MOCK_METHOD1(setStart, void(const Point& start));
    MOCK_CONST_METHOD0(getStart, const Point&());
    MOCK_METHOD0(getStart, Point&());

    MOCK_METHOD1(setEnd, void(const Point& end));
    MOCK_CONST_METHOD0(getEnd, const Point&());
    MOCK_METHOD0(getEnd, Point&());

    MOCK_METHOD2(setSegment, void(const Point& start, const Point& end));
    MOCK_METHOD0(computeTangent, const Vector2d&());
    MOCK_CONST_METHOD0(getTangent, const Vector2d&());

    MOCK_CONST_METHOD1(pointOnTheRightSide, int(const Point& point));
};

class MockPolygon : public IPolygon {
  public:
    MOCK_CONST_METHOD0(getNumberVertices, unsigned int());
    MOCK_CONST_METHOD0(getVertices, const vector<Point>&());
    MOCK_METHOD2(setVertexAtPosition, void(const Point& vertex, const int& position));
    MOCK_METHOD1(appendVertex, void(const Point& vertex));
    MOCK_METHOD2(insertVertexAtPosition, void(const Point& vertex, const int& position));
    MOCK_CONST_METHOD1(getVertexAtPosition, const Point&(const int& position));
    MOCK_CONST_METHOD1(nextVertexId, int(unsigned int id));
    MOCK_CONST_METHOD0(getLastVertex, const Point&());

    MOCK_CONST_METHOD0(ComputeArea, double());

    MOCK_CONST_METHOD0(getEdges, const vector<Segment>&());

    MOCK_METHOD2(setVertexLabelAtPosition, void(const int& position, int label));
    MOCK_CONST_METHOD1(getVertexLabelAtPosition, int(const int& position));
    MOCK_METHOD1(setVertexLabels, void(const vector<unsigned int> &polygonVertices));
    MOCK_METHOD0(setDefaultVertexLabels, void());
    MOCK_METHOD1(pointInPolygon, bool(const Point& point));
    MOCK_CONST_METHOD1(isPolygonOnTheRightSide, int(const Segment &line));
    MOCK_METHOD0(buildUpPolygonEdges, void());
};

class MockIntersector1D1D : public IIntersector1D1D {
  public:
    MOCK_METHOD2(SetFirstSegment, void(const Vector2d& origin, const Vector2d& end));
    MOCK_METHOD1(SetFirstSegment, void(const Segment& s));
    MOCK_METHOD2(SetSecondSegment, void(const Vector2d& origin, const Vector2d& end));
    MOCK_METHOD1(SetSecondSegment, void(const Segment& s));

    MOCK_METHOD0(ComputeIntersection, bool());
    MOCK_METHOD0(ParametricCoordinates, const Vector2d&());
    MOCK_METHOD0(FirstParametricCoordinate, const double&());
    MOCK_METHOD0(SecondParametricCoordinate, const double&());
    MOCK_METHOD0(PositionIntersectionInFirstEdge, const Position&());
    MOCK_METHOD0(PositionIntersectionInSecondEdge, const Position&());
    MOCK_METHOD0(TypeIntersection, const Type&());
    MOCK_CONST_METHOD2(IntersectionFirstParametricCoordinate, Vector2d(const Vector2d& origin,const Vector2d& end));
    MOCK_CONST_METHOD1(IntersectionFirstParametricCoordinate, Vector2d(const Segment& s));
    MOCK_CONST_METHOD2(IntersectionSecondParametricCoordinate, Vector2d(const Vector2d& origin,const Vector2d& end));
};

  TEST(TestIntersectorPolygonLine, TestFindIntersectionVertices)
  {

    vector<Point> polygonVertices;
    polygonVertices.resize(5);
    polygonVertices[0] = Point(0, 0);
    polygonVertices[1] = Point(4, 0);
    polygonVertices[2] = Point(2, 2);
    polygonVertices[3] = Point(4, 4);
    polygonVertices[4] = Point(0, 4);

    Point start(3, 0.5);
    Point end(3, 3.5);
    Vector2d tangent = Vector2d(0, 3);

    vector<double> parametric;
    parametric.resize(4);
    parametric[0] = -0.1666666667;
    parametric[1] = 0.16666666667;
    parametric[2] = 0.83333333333;
    parametric[3] = 1.16666666667;

    vector<Segment> edges;
    edges.resize(5);
    edges[0] = Segment(Point(0, 0), Point(4, 0));
    edges[1] = Segment(Point(4, 0), Point(2, 2));
    edges[2] = Segment(Point(2, 2), Point(4, 4));
    edges[3] = Segment(Point(4, 4), Point(0, 4));
    edges[4] = Segment(Point(0, 4), Point(0, 0));

    Point intp1(3, 0);
    Point intp2(3, 1);
    Point intp3(3, 3);
    Point intp4(3, 4);

    Intersector1D1D::Type type = Intersector1D1D::Type::IntersectionOnSegment;

    MockSegment segment;
    MockPolygon polygon;
    MockIntersector1D1D intersector1d1d;

    EXPECT_CALL(segment, getStart())
            .WillRepeatedly(ReturnRef(start));
    EXPECT_CALL(segment, getEnd())
            .WillRepeatedly(ReturnRef(end));
    EXPECT_CALL(segment, computeTangent)
            .WillRepeatedly(ReturnRef(tangent));

    EXPECT_CALL(polygon, getNumberVertices)
            .WillRepeatedly(Return(5));
    EXPECT_CALL(polygon, getEdges)
            .WillRepeatedly(ReturnRef(edges));

    EXPECT_CALL(intersector1d1d, TypeIntersection)
            .WillRepeatedly(ReturnRef(type));
    EXPECT_CALL(intersector1d1d, ComputeIntersection)
            .WillOnce(Return(true))
            .WillOnce(Return(true))
            .WillOnce(Return(true))
            .WillOnce(Return(true))
            .WillOnce(Return(false));
    EXPECT_CALL(intersector1d1d, IntersectionFirstParametricCoordinate(_, _))
            .WillOnce(Return(Vector2d(3, 0)))
            .WillOnce(Return(Vector2d(3, 1)))
            .WillOnce(Return(Vector2d(3, 3)))
            .WillOnce(Return(Vector2d(3, 4)));
    EXPECT_CALL(intersector1d1d, FirstParametricCoordinate)
            .WillOnce(ReturnRef(parametric[0]))
            .WillOnce(ReturnRef(parametric[1]))
            .WillOnce(ReturnRef(parametric[2]))
            .WillOnce(ReturnRef(parametric[3]));

    IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
    vector<Point> intersectionPoints = intersector.findIntersectionVertices();

    try
    {
      EXPECT_EQ(intersectionPoints[0].getPointLabel(), 7);
      EXPECT_EQ(intersectionPoints[1].getPointLabel(), 8);
      EXPECT_EQ(intersectionPoints[2].getPointLabel(), 9);
      EXPECT_EQ(intersectionPoints[3].getPointLabel(), 10);
      EXPECT_EQ(Point(intersectionPoints[0].getCoordinates()), intp1);
      EXPECT_EQ(Point(intersectionPoints[1].getCoordinates()), intp2);
      EXPECT_EQ(Point(intersectionPoints[2].getCoordinates()), intp3);
      EXPECT_EQ(Point(intersectionPoints[3].getCoordinates()), intp4);

    }
    catch (const exception& exception)
    {
      FAIL();
    }

  }

  TEST(TestIntersectorPolygonLine, TestFindNewPoints)
  {
    vector<Point> polygonVertices;
    polygonVertices.resize(5);
    polygonVertices[0] = Point(0, 0);
    polygonVertices[1] = Point(4, 0);
    polygonVertices[2] = Point(2, 2);
    polygonVertices[3] = Point(4, 4);
    polygonVertices[4] = Point(0, 4);

    Point start(3, 0.5);
    Point end(3, 3.5);
    Vector2d tangent = Vector2d(0, 3);

    vector<double> parametric;
    parametric.resize(4);
    parametric[0] = -0.1666666667;
    parametric[1] = 0.16666666667;
    parametric[2] = 0.83333333333;
    parametric[3] = 1.16666666667;

    vector<Segment> edges;
    edges.resize(5);
    edges[0] = Segment(Point(0, 0), Point(4, 0));
    edges[1] = Segment(Point(4, 0), Point(2, 2));
    edges[2] = Segment(Point(2, 2), Point(4, 4));
    edges[3] = Segment(Point(4, 4), Point(0, 4));
    edges[4] = Segment(Point(0, 4), Point(0, 0));

    Point intp1(3, 0);
    Point intp2(3, 1);
    Point intp3(3, 3);
    Point intp4(3, 4);

    Intersector1D1D::Type type = Intersector1D1D::Type::IntersectionOnSegment;

    MockSegment segment;
    MockIntersector1D1D intersector1d1d;
    MockPolygon polygon;

    EXPECT_CALL(polygon, getNumberVertices)
            .WillRepeatedly(Return(5));
    EXPECT_CALL(polygon, getEdges)
            .WillRepeatedly(ReturnRef(edges));
    EXPECT_CALL(polygon, getVertices)
            .WillRepeatedly(ReturnRef(polygonVertices));
    EXPECT_CALL(polygon, nextVertexId(0)).WillRepeatedly(Return(1));
    EXPECT_CALL(polygon, nextVertexId(1)).WillRepeatedly(Return(2));
    EXPECT_CALL(polygon, nextVertexId(2)).WillRepeatedly(Return(3));
    EXPECT_CALL(polygon, nextVertexId(3)).WillRepeatedly(Return(4));
    EXPECT_CALL(polygon, nextVertexId(4)).WillRepeatedly(Return(0));

    EXPECT_CALL(intersector1d1d, TypeIntersection)
            .WillRepeatedly(ReturnRef(type));

    try
    {
      EXPECT_CALL(segment, getStart())
              .WillRepeatedly(ReturnRef(start));
      EXPECT_CALL(segment, getEnd())
              .WillRepeatedly(ReturnRef(end));
      EXPECT_CALL(segment, computeTangent)
              .WillRepeatedly(ReturnRef(tangent));

      EXPECT_CALL(intersector1d1d, ComputeIntersection)
              .WillOnce(Return(true))
              .WillOnce(Return(true))
              .WillOnce(Return(true))
              .WillOnce(Return(true))
              .WillOnce(Return(false));
      EXPECT_CALL(intersector1d1d, IntersectionFirstParametricCoordinate(_, _))
              .WillOnce(Return(Vector2d(3, 0)))
              .WillOnce(Return(Vector2d(3, 1)))
              .WillOnce(Return(Vector2d(3, 3)))
              .WillOnce(Return(Vector2d(3, 4)));
      EXPECT_CALL(intersector1d1d, FirstParametricCoordinate)
              .WillOnce(ReturnRef(parametric[0]))
              .WillOnce(ReturnRef(parametric[1]))
              .WillOnce(ReturnRef(parametric[2]))
              .WillOnce(ReturnRef(parametric[3]));

      IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
      vector<Point> intersectionPoints = intersector.findIntersectionVertices();
      vector<Polygon> newPolygons = intersector.findPolygons();
      vector<Point> newPoints = intersector.findNewPoints();

      EXPECT_EQ(newPoints.size(), 6);
      EXPECT_EQ(newPoints[0].getPointLabel(), 5);
      EXPECT_EQ(newPoints[1].getPointLabel(), 6);
      EXPECT_EQ(newPoints[2].getPointLabel(), 7);
      EXPECT_EQ(newPoints[3].getPointLabel(), 8);
      EXPECT_EQ(newPoints[4].getPointLabel(), 9);
      EXPECT_EQ(newPoints[5].getPointLabel(), 10);
      EXPECT_TRUE(intersector.getStartFound());
      EXPECT_TRUE(intersector.getEndFound());
      EXPECT_EQ(Point(newPoints[0].getCoordinates()), segment.getStart());
      EXPECT_EQ(Point(newPoints[1].getCoordinates()), segment.getEnd());
      EXPECT_EQ(Point(newPoints[2].getCoordinates()), intp1);
      EXPECT_EQ(Point(newPoints[3].getCoordinates()), intp2);
      EXPECT_EQ(Point(newPoints[4].getCoordinates()), intp3);
      EXPECT_EQ(Point(newPoints[5].getCoordinates()), intp4);

    }
    catch (const exception& exception)
    {
      FAIL();
    }
    Point start2(3,2);
    Point end2(3, 3.5);
    Vector2d tangent2 = Vector2d(0, 1.5);

    vector<double> parametric2;
    parametric2.resize(4);
    parametric2[0] = -1.3333333333;
    parametric2[1] = -0.6666666667;
    parametric2[2] = 0.66666666667;
    parametric2[3] = 1.33333333333;

    try
    {
      EXPECT_CALL(segment, getStart())
              .WillRepeatedly(ReturnRef(start2));
      EXPECT_CALL(segment, getEnd())
              .WillRepeatedly(ReturnRef(end2));
      EXPECT_CALL(segment, computeTangent)
              .WillRepeatedly(ReturnRef(tangent2));

      EXPECT_CALL(intersector1d1d, ComputeIntersection)
              .WillOnce(Return(true))
              .WillOnce(Return(true))
              .WillOnce(Return(true))
              .WillOnce(Return(true))
              .WillOnce(Return(false));
      EXPECT_CALL(intersector1d1d, IntersectionFirstParametricCoordinate(_, _))
              .WillOnce(Return(Vector2d(3, 0)))
              .WillOnce(Return(Vector2d(3, 1)))
              .WillOnce(Return(Vector2d(3, 3)))
              .WillOnce(Return(Vector2d(3, 4)));
      EXPECT_CALL(intersector1d1d, FirstParametricCoordinate)
              .WillOnce(ReturnRef(parametric2[0]))
              .WillOnce(ReturnRef(parametric2[1]))
              .WillOnce(ReturnRef(parametric2[2]))
              .WillOnce(ReturnRef(parametric2[3]));

      IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
      vector<Point> intersectionPoints = intersector.findIntersectionVertices();
      vector<Polygon> newPolygons = intersector.findPolygons();
      vector<Point> newPoints = intersector.findNewPoints();
      EXPECT_EQ(newPoints.size(), 5);

      EXPECT_EQ(newPoints[0].getPointLabel(), 6);
      EXPECT_EQ(newPoints[1].getPointLabel(), 7);
      EXPECT_EQ(newPoints[2].getPointLabel(), 8);
      EXPECT_EQ(newPoints[3].getPointLabel(), 9);
      EXPECT_EQ(newPoints[4].getPointLabel(), 10);

      EXPECT_FALSE(intersector.getStartFound());
      EXPECT_TRUE(intersector.getEndFound());
      EXPECT_EQ(Point(newPoints[0].getCoordinates()), segment.getEnd());
      EXPECT_EQ(Point(newPoints[1].getCoordinates()), intp1);
      EXPECT_EQ(Point(newPoints[2].getCoordinates()), intp2);
      EXPECT_EQ(Point(newPoints[3].getCoordinates()), intp3);
      EXPECT_EQ(Point(newPoints[4].getCoordinates()), intp4);

    }
    catch (const exception& exception)
    {
      FAIL();
    }
  }

  TEST(TestIntersectorPolygonLine, TestExtendPolygonIfEndpointsOnEdge)
  {

      vector<Point> polygonVertices;
      polygonVertices.resize(5);
      polygonVertices[0] = Point(0, 0);
      polygonVertices[1] = Point(4, 0);
      polygonVertices[2] = Point(2, 2);
      polygonVertices[3] = Point(4, 4);
      polygonVertices[4] = Point(0, 4);

      // setting labels
      polygonVertices[0].setPointLabel(0);
      polygonVertices[1].setPointLabel(1);
      polygonVertices[2].setPointLabel(2);
      polygonVertices[3].setPointLabel(3);
      polygonVertices[4].setPointLabel(4);

      Point start(3, 0.5);
      Point end(3, 3.5);
      Vector2d tangent = Vector2d(0, 3);

      vector<double> parametric;
      parametric.resize(4);
      parametric[0] = -0.1666666667;
      parametric[1] = 0.16666666667;
      parametric[2] = 0.83333333333;
      parametric[3] = 1.16666666667;

      vector<Segment> edges;
      edges.resize(5);
      edges[0] = Segment(Point(0, 0), Point(4, 0));
      edges[1] = Segment(Point(4, 0), Point(2, 2));
      edges[2] = Segment(Point(2, 2), Point(4, 4));
      edges[3] = Segment(Point(4, 4), Point(0, 4));
      edges[4] = Segment(Point(0, 4), Point(0, 0));

      Point intp1(3, 0);
      Point intp2(3, 1);
      Point intp3(3, 3);
      Point intp4(3, 4);

      Intersector1D1D::Type type = Intersector1D1D::Type::IntersectionOnSegment;

      MockSegment segment;
      MockIntersector1D1D intersector1d1d;
      MockPolygon polygon;

      EXPECT_CALL(segment, getStart())
              .WillRepeatedly(ReturnRef(start));
      EXPECT_CALL(segment, getEnd())
              .WillRepeatedly(ReturnRef(end));
      EXPECT_CALL(segment, computeTangent)
              .WillRepeatedly(ReturnRef(tangent));

      EXPECT_CALL(polygon, getNumberVertices)
              .WillRepeatedly(Return(5));
      EXPECT_CALL(polygon, getEdges)
              .WillRepeatedly(ReturnRef(edges));
      EXPECT_CALL(polygon, getVertices)
              .WillRepeatedly(ReturnRef(polygonVertices));
      EXPECT_CALL(polygon, nextVertexId(0)).WillRepeatedly(Return(1));
      EXPECT_CALL(polygon, nextVertexId(1)).WillRepeatedly(Return(2));
      EXPECT_CALL(polygon, nextVertexId(2)).WillRepeatedly(Return(3));
      EXPECT_CALL(polygon, nextVertexId(3)).WillRepeatedly(Return(4));
      EXPECT_CALL(polygon, nextVertexId(4)).WillRepeatedly(Return(0));

      EXPECT_CALL(intersector1d1d, TypeIntersection)
              .WillRepeatedly(ReturnRef(type));

      EXPECT_CALL(intersector1d1d, ComputeIntersection)
              .WillOnce(Return(true))
              .WillOnce(Return(true))
              .WillOnce(Return(true))
              .WillOnce(Return(true))
              .WillOnce(Return(false));
      EXPECT_CALL(intersector1d1d, IntersectionFirstParametricCoordinate(_, _))
              .WillOnce(Return(Vector2d(3, 0)))
              .WillOnce(Return(Vector2d(3, 1)))
              .WillOnce(Return(Vector2d(3, 3)))
              .WillOnce(Return(Vector2d(3, 4)));
      EXPECT_CALL(intersector1d1d, FirstParametricCoordinate)
              .WillOnce(ReturnRef(parametric[0]))
              .WillOnce(ReturnRef(parametric[1]))
              .WillOnce(ReturnRef(parametric[2]))
              .WillOnce(ReturnRef(parametric[3]));

      IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
      vector<Point> intersectionPoints = intersector.findIntersectionVertices();
      vector<Polygon> newPolygons = intersector.findPolygons();
      vector<Polygon> newExtendedPolygons = intersector.getExtendedPolygons();

      try
      {
      EXPECT_EQ(newPolygons[0].getNumberVertices(), 7);
      EXPECT_EQ(newPolygons[1].getNumberVertices(), 3);
      EXPECT_EQ(newPolygons[2].getNumberVertices(), 3);
      EXPECT_EQ(newExtendedPolygons[0].getNumberVertices(), 9);
      EXPECT_EQ(newExtendedPolygons[1].getNumberVertices(), 4);
      EXPECT_EQ(newExtendedPolygons[2].getNumberVertices(), 4);
      EXPECT_TRUE(intersector.getStartFound());
      EXPECT_TRUE(intersector.getEndFound());

      //Polygon 0-7--8-2-9--10-4
      EXPECT_EQ(newPolygons[0].getVertexLabelAtPosition(1), 7);
      EXPECT_EQ(newPolygons[0].getVertexLabelAtPosition(2), 8);
      EXPECT_EQ(newPolygons[0].getVertexLabelAtPosition(4), 9);
      EXPECT_EQ(newPolygons[0].getVertexLabelAtPosition(5), 10);

      //Polygon 0-7-5-8-2-9-6-10-4
      EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(1), 7);
      EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(2), 5);
      EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(3), 8);
      EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(5), 9);
      EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(6), 6);
      EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(7), 10);

      //Polygon 1-8--7
      EXPECT_EQ(newPolygons[1].getVertexLabelAtPosition(0), 1);
      EXPECT_EQ(newPolygons[1].getVertexLabelAtPosition(1), 8);
      EXPECT_EQ(newPolygons[1].getVertexLabelAtPosition(2), 7);

      //Polygon 1-8-5-7
      EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(0), 1);
      EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(1), 8);
      EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(2), 5);
      EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(3), 7);
      }
      catch (const exception& exception)
      {
       FAIL();
      }

  }

  TEST(TestIntersectorPolygonLine, FindPolygons1a) //concave hexagon
  {
    vector<Point> polygonVertices;
    polygonVertices.resize(6);

    polygonVertices[0] = Point(1.5, 1.0);
    polygonVertices[1] = Point(5.6, 1.5);
    polygonVertices[2] = Point(5.5, 4.8);
    polygonVertices[3] = Point(4.0, 6.2);
    polygonVertices[4] = Point(3.2, 4.2);
    polygonVertices[5] = Point(1.0, 4.0);

    Polygon polygon(polygonVertices);

    Point start(2.0, 3.7);
    Point end(4.1, 5.9);
    Segment segment(start, end);

    Intersector1D1D intersector1d1d;
    IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
    vector<Point> intersectionPoints = intersector.findIntersectionVertices();
    vector<Polygon> newPolygons = intersector.findPolygons();
    vector<Point> newPoints = intersector.findNewPoints();
    vector<Polygon> newExtendedPolygons = intersector.getExtendedPolygons();

    try
    {
      EXPECT_EQ(newPolygons.size(), 3);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    try
    {
      EXPECT_EQ(newPolygons[0].getNumberVertices(), 8);
      EXPECT_EQ(newPolygons[1].getNumberVertices(), 3);
      EXPECT_EQ(newPolygons[2].getNumberVertices(), 3);
      EXPECT_EQ(newExtendedPolygons[0].getNumberVertices(), 10);
      EXPECT_EQ(newExtendedPolygons[1].getNumberVertices(), 4);
      EXPECT_EQ(newExtendedPolygons[2].getNumberVertices(), 4);
    }
    catch (const exception& exception)
    {
      FAIL();
    }


    try
    {
    //Polygon 0-1-2-11-7-10-4-9-6-8-0
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(3), 11);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(4), 7);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(5), 10);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(6), 4);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(7), 9);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(8), 6);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(9), 8);
    //Polygon 3-10-7-11
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(0), 3);
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(1), 10);
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(2), 7);
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(3), 11);
    //Polygon 5-8-6-9
    EXPECT_EQ(newExtendedPolygons[2].getVertexLabelAtPosition(0), 5);
    EXPECT_EQ(newExtendedPolygons[2].getVertexLabelAtPosition(1), 8);
    EXPECT_EQ(newExtendedPolygons[2].getVertexLabelAtPosition(2), 6);
    EXPECT_EQ(newExtendedPolygons[2].getVertexLabelAtPosition(3), 9);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

  }

  TEST(TestIntersectorPolygonLine, FindPolygons1b) //concave hexagon swapped segment endpoints
  {
    vector<Point> polygonVertices;
    polygonVertices.resize(6);

    polygonVertices[0] = Point(1.5, 1.0);
    polygonVertices[1] = Point(5.6, 1.5);
    polygonVertices[2] = Point(5.5, 4.8);
    polygonVertices[3] = Point(4.0, 6.2);
    polygonVertices[4] = Point(3.2, 4.2);
    polygonVertices[5] = Point(1.0, 4.0);

    Polygon polygon(polygonVertices);

    Point end(2.0, 3.7);
    Point start(4.1, 5.9);
    Segment segment(start, end);

    Intersector1D1D intersector1d1d;
    IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
    vector<Point> intersectionPoints = intersector.findIntersectionVertices();
    vector<Polygon> newPolygons = intersector.findPolygons();
    vector<Point> newPoints = intersector.findNewPoints();
    vector<Polygon> newExtendedPolygons = intersector.getExtendedPolygons();

    try
    {
      EXPECT_EQ(newPolygons.size(), 3);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    try
    {
      EXPECT_EQ(newPolygons[0].getNumberVertices(), 8);
      EXPECT_EQ(newPolygons[1].getNumberVertices(), 3);
      EXPECT_EQ(newPolygons[2].getNumberVertices(), 3);
      EXPECT_EQ(newExtendedPolygons[0].getNumberVertices(), 10);
      EXPECT_EQ(newExtendedPolygons[1].getNumberVertices(), 4);
      EXPECT_EQ(newExtendedPolygons[2].getNumberVertices(), 4);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    try
    {
    //Polygon 0-1-2-8-6-9-4-10-7-11
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(3), 8);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(4), 6);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(5), 9);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(6), 4);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(7), 10);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(8), 7);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(9), 11);
    //Polygon 3-9-6-8
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(0), 3);
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(1), 9);
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(2), 6);
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(3), 8);
    //Polygon 5-11-7-10
    EXPECT_EQ(newExtendedPolygons[2].getVertexLabelAtPosition(0), 5);
    EXPECT_EQ(newExtendedPolygons[2].getVertexLabelAtPosition(1), 11);
    EXPECT_EQ(newExtendedPolygons[2].getVertexLabelAtPosition(2), 7);
    EXPECT_EQ(newExtendedPolygons[2].getVertexLabelAtPosition(3), 10);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

  }

  TEST(TestIntersectorPolygonLine, FindPolygons1c) //concave hexagon , start/end consecutive
  {
    vector<Point> polygonVertices;
    polygonVertices.resize(6);

    polygonVertices[0] = Point(1.5, 1.0);
    polygonVertices[1] = Point(5.6, 1.5);
    polygonVertices[2] = Point(5.5, 4.8);
    polygonVertices[3] = Point(4.0, 6.2);
    polygonVertices[4] = Point(3.2, 4.2);
    polygonVertices[5] = Point(1.0, 4.0);

    Polygon polygon(polygonVertices);

    Point start(2.0, 3.7);
    Vector2d p1(2.0, 3.7);
    Vector2d p2(4.1, 5.9);
    Vector2d p3 = 0.9 * p1 + 0.1 * p2;
    Point end(p3);

    Segment segment(start, end);

    Intersector1D1D intersector1d1d;
    IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
    vector<Point> intersectionPoints = intersector.findIntersectionVertices();
    vector<Polygon> newPolygons = intersector.findPolygons();
    vector<Point> newPoints = intersector.findNewPoints();
    vector<Polygon> newExtendedPolygons = intersector.getExtendedPolygons();

    try
    {
      EXPECT_EQ(newPolygons.size(), 3);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    try
    {
      EXPECT_EQ(newPolygons[0].getNumberVertices(), 8);
      EXPECT_EQ(newPolygons[1].getNumberVertices(), 3);
      EXPECT_EQ(newPolygons[2].getNumberVertices(), 3);
      EXPECT_EQ(newExtendedPolygons[0].getNumberVertices(), 10);
      EXPECT_EQ(newExtendedPolygons[1].getNumberVertices(), 3);
      EXPECT_EQ(newExtendedPolygons[2].getNumberVertices(), 5);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    try
    {
    //Polygon 0-1-2-11-7-10-4-9-7-6-8
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(3), 11);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(4), 10);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(5), 4);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(6), 9);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(7), 7);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(8), 6);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(9), 8);

    //Polygon 3-10-11
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(0), 3);
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(1), 10);
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(2), 11);
    //Polygon 5-8-6-7-9
    EXPECT_EQ(newExtendedPolygons[2].getVertexLabelAtPosition(0), 5);
    EXPECT_EQ(newExtendedPolygons[2].getVertexLabelAtPosition(1), 8);
    EXPECT_EQ(newExtendedPolygons[2].getVertexLabelAtPosition(2), 6);
    EXPECT_EQ(newExtendedPolygons[2].getVertexLabelAtPosition(3), 7);
    EXPECT_EQ(newExtendedPolygons[2].getVertexLabelAtPosition(4), 9);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

  }

  TEST(TestIntersectorPolygonLine, FindPolygons1d) //concave hexagon, start in/ end out
  {
    vector<Point> polygonVertices;
    polygonVertices.resize(6);

    polygonVertices[0] = Point(1.5, 1.0);
    polygonVertices[1] = Point(5.6, 1.5);
    polygonVertices[2] = Point(5.5, 4.8);
    polygonVertices[3] = Point(4.0, 6.2);
    polygonVertices[4] = Point(3.2, 4.2);
    polygonVertices[5] = Point(1.0, 4.0);

    Polygon polygon(polygonVertices);


    Point start(2.0, 3.7);
    Point end(3.06, 4.81);
    Segment segment(start, end);

    Intersector1D1D intersector1d1d;
    IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
    vector<Point> intersectionPoints = intersector.findIntersectionVertices();
    vector<Polygon> newPolygons = intersector.findPolygons();
    vector<Point> newPoints = intersector.findNewPoints();
    vector<Polygon> newExtendedPolygons = intersector.getExtendedPolygons();

    try
    {
      EXPECT_EQ(newPolygons.size(), 3);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    try
    {
      EXPECT_EQ(newPolygons[0].getNumberVertices(), 8);
      EXPECT_EQ(newPolygons[1].getNumberVertices(), 3);
      EXPECT_EQ(newPolygons[2].getNumberVertices(), 3);
      EXPECT_EQ(newExtendedPolygons[0].getNumberVertices(), 9);
      EXPECT_EQ(newExtendedPolygons[1].getNumberVertices(), 3);
      EXPECT_EQ(newExtendedPolygons[2].getNumberVertices(), 4);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    try
    {
    //Polygon 0-1-2-11-10-4-9-6-8
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(3), 11);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(4), 10);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(5), 4);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(6), 9);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(7), 6);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(8), 8);
    //Polygon 3-10-11
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(0), 3);
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(1), 10);
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(2), 11);
    //Polygon 5-8-6-9
    EXPECT_EQ(newExtendedPolygons[2].getVertexLabelAtPosition(0), 5);
    EXPECT_EQ(newExtendedPolygons[2].getVertexLabelAtPosition(1), 8);
    EXPECT_EQ(newExtendedPolygons[2].getVertexLabelAtPosition(2), 6);
    EXPECT_EQ(newExtendedPolygons[2].getVertexLabelAtPosition(3), 9);
    }
    catch (const exception& exception)
    {
      FAIL();
    }


  }

  TEST(TestIntersectorPolygonLine, FindPolygons1e) //concave hexagon, start out/ end out
  {
    vector<Point> polygonVertices;
    polygonVertices.resize(6);

    polygonVertices[0] = Point(1.5, 1.0);
    polygonVertices[1] = Point(5.6, 1.5);
    polygonVertices[2] = Point(5.5, 4.8);
    polygonVertices[3] = Point(4.0, 6.2);
    polygonVertices[4] = Point(3.2, 4.2);
    polygonVertices[5] = Point(1.0, 4.0);

    Polygon polygon(polygonVertices);

    Point start(3.06, 4.81);
    Point end(4.8, 6.1);
    Segment segment(start, end);

    Intersector1D1D intersector1d1d;
    IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
    vector<Point> intersectionPoints = intersector.findIntersectionVertices();
    vector<Polygon> newPolygons = intersector.findPolygons();
    vector<Point> newPoints = intersector.findNewPoints();
    vector<Polygon> newExtendedPolygons = intersector.getExtendedPolygons();

    try
    {
      EXPECT_EQ(newPolygons.size(), 3);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    try
    {
      EXPECT_EQ(newPolygons[0].getNumberVertices(), 8);
      EXPECT_EQ(newPolygons[1].getNumberVertices(), 3);
      EXPECT_EQ(newPolygons[2].getNumberVertices(), 3);
      EXPECT_EQ(newExtendedPolygons[0].getNumberVertices(), 8);
      EXPECT_EQ(newExtendedPolygons[1].getNumberVertices(), 3);
      EXPECT_EQ(newExtendedPolygons[2].getNumberVertices(), 3);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    try
    {
    //Polygon 0-1-2-11-10-4-9-8
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(3), 11);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(4), 10);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(5), 4);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(6), 9);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(7), 8);
    //Polygon 3-10-11
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(0), 3);
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(1), 10);
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(2), 11);
    //Polygon 5-8-9
    EXPECT_EQ(newExtendedPolygons[2].getVertexLabelAtPosition(0), 5);
    EXPECT_EQ(newExtendedPolygons[2].getVertexLabelAtPosition(1), 8);
    EXPECT_EQ(newExtendedPolygons[2].getVertexLabelAtPosition(2), 9);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

  }

  TEST(TestIntersectorPolygonLine, FindPolygons2a)//convex pentagon with segment aligned with a vertex
  {
    vector<Point> polygonVertices;
    polygonVertices.resize(5);

    polygonVertices[0] = Point(2.5, 1.0);
    polygonVertices[1] = Point(4.0, 2.1);
    polygonVertices[2] = Point(3.4, 4.2);
    polygonVertices[3] = Point(1.6, 4.2);
    polygonVertices[4] = Point(1.0, 2.1);

    Polygon polygon(polygonVertices);

    Point start(1.4, 2.75);
    Point end(3.6, 2.2);
    Segment segment(start, end);

    Intersector1D1D intersector1d1d;
    IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
    vector<Point> intersectionPoints = intersector.findIntersectionVertices();
    vector<Polygon> newPolygons = intersector.findPolygons();
    vector<Point> newPoints = intersector.findNewPoints();
    vector<Polygon> newExtendedPolygons = intersector.getExtendedPolygons();

    try
    {
      EXPECT_EQ(newPolygons.size(), 2);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    try
    {
      EXPECT_EQ(newPolygons[0].getNumberVertices() , 4);
      EXPECT_EQ(newPolygons[1].getNumberVertices(), 4);
      EXPECT_EQ(newExtendedPolygons[0].getNumberVertices() , 6);
      EXPECT_EQ(newExtendedPolygons[1].getNumberVertices(), 6);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    try
    {
    //Polygon 0-1-6-5-7-4
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(0), 0);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(1), 1);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(2), 6);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(3), 5);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(4), 7);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(5), 4);
    //Polygon 2-3-7-5-6-1
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(0), 1);
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(1), 2);
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(2), 3);
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(3), 7);
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(4), 5);
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(5), 6);
    }
    catch (const exception& exception)
    {
      FAIL();
    }


  }

  TEST(TestIntersectorPolygonLine, FindPolygons2b)//convex pentagon with segment passing through 2 vertices
  {
    vector<Point> polygonVertices;
    polygonVertices.resize(5);

    polygonVertices[0] = Point(2.5, 1.0);
    polygonVertices[1] = Point(4.0, 2.1);
    polygonVertices[2] = Point(3.4, 4.2);
    polygonVertices[3] = Point(1.6, 4.2);
    polygonVertices[4] = Point(1.0, 2.1);

    Polygon polygon(polygonVertices);

    Point start(0.0, 2.1);
    Point end(5, 2.1);
    Segment segment(start, end);

    Intersector1D1D intersector1d1d;
    IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
    vector<Point> intersectionPoints = intersector.findIntersectionVertices();
    vector<Polygon> newPolygons = intersector.findPolygons();
    vector<Point> newPoints = intersector.findNewPoints();
    vector<Polygon> newExtendedPolygons = intersector.getExtendedPolygons();

    try
    {
      EXPECT_EQ(newPolygons.size(), 2);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    try
    {
      EXPECT_EQ(newPolygons[0].getNumberVertices() , 3);
      EXPECT_EQ(newPolygons[1].getNumberVertices(), 4);
      EXPECT_EQ(newExtendedPolygons[0].getNumberVertices() , 3);
      EXPECT_EQ(newExtendedPolygons[1].getNumberVertices(), 4);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    try
    {
    //Polygon 0-1-4
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(0), 0);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(1), 1);
    EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(2), 4);
    //Polygon 1-2-3-4
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(0), 1);
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(1), 2);
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(2), 3);
    EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(3), 4);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

  }

  TEST(TestIntersectorPolygonLine, FindPolygons3)
  {
    vector<Point> polygonVertices;
    polygonVertices.resize(8);

    polygonVertices[0] = Point(0, 0);
    polygonVertices[1] = Point(8, 0);
    polygonVertices[2] = Point(4.64, 1.5);
    polygonVertices[3] = Point(8.93, 4.48);
    polygonVertices[4] = Point(2.18, 5.36);
    polygonVertices[5] = Point(5.52, 9.22);
    polygonVertices[6] = Point(0, 5);
    polygonVertices[7] = Point(6, 4);

    Polygon polygon(polygonVertices);

    Point start(7.28, -0.72);
    Point end(1.2, 9.14);
    Segment segment(start, end);

    Intersector1D1D intersector1d1d;
    IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
    vector<Point> intersectionPoints = intersector.findIntersectionVertices();
    vector<Polygon> newPolygons = intersector.findPolygons();
    vector<Point> newPoints = intersector.findNewPoints();
    vector<Polygon> newExtendedPolygons = intersector.getExtendedPolygons();

    try
    {
      EXPECT_EQ(newPolygons.size(), 5);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    try
    {
      EXPECT_EQ(newPolygons[0].getNumberVertices(), 6);
      EXPECT_EQ(newPolygons[1].getNumberVertices(), 3);
      EXPECT_EQ(newPolygons[2].getNumberVertices(), 6);
      EXPECT_EQ(newPolygons[3].getNumberVertices(), 6);
      EXPECT_EQ(newPolygons[4].getNumberVertices(), 3);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

  }

  TEST(TestIntersectorPolygonLine, FindPolygons4)// segmento finisce in un vertice
  {
    vector<Point> polygonVertices;
    polygonVertices.resize(8);

    polygonVertices[0] = Point(0, 0);
    polygonVertices[1] = Point(8, 0);
    polygonVertices[2] = Point(4.64, 1.5);
    polygonVertices[3] = Point(8.93, 4.48);
    polygonVertices[4] = Point(2.18, 5.36);
    polygonVertices[5] = Point(5.52, 9.22);
    polygonVertices[6] = Point(0, 5);
    polygonVertices[7] = Point(6, 4);

    Polygon polygon(polygonVertices);

    Point start(7.28, -0.72);
    Point end(5.52, 9.22); //=polygonVertices[5]
    Segment segment(start, end);

    Intersector1D1D intersector1d1d;
    IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
    vector<Point> intersectionPoints = intersector.findIntersectionVertices();
    vector<Polygon> newPolygons = intersector.findPolygons();
    vector<Point> newPoints = intersector.findNewPoints();
    vector<Polygon> newExtendedPolygons = intersector.getExtendedPolygons();

    try
    {
      EXPECT_EQ(newPolygons.size(), 3);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    try
    {
      EXPECT_EQ(newPolygons[0].getNumberVertices(), 10);
      EXPECT_EQ(newPolygons[1].getNumberVertices(), 3);
      EXPECT_EQ(newPolygons[2].getNumberVertices(), 3);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

  }

  TEST(TestIntersectorPolygonLine, FindPolygons5) //TEST FACILE1- square, endpoints outside
    {
      vector<Point> polygonVertices;
      polygonVertices.resize(4);

      polygonVertices[0] = Point(0, 0);
      polygonVertices[1] = Point(4, 0);
      polygonVertices[2] = Point(4, 4);
      polygonVertices[3] = Point(0, 4);


      Polygon polygon(polygonVertices);

      Point end(5, 1);
      Point start(2, 5);
      Segment segment(start, end);

      Intersector1D1D intersector1d1d;
      IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
      vector<Point> intersectionPoints = intersector.findIntersectionVertices();
      vector<Polygon> newPolygons = intersector.findPolygons();
      vector<Point> newPoints = intersector.findNewPoints();
      vector<Polygon> newExtendedPolygons = intersector.getExtendedPolygons();

      try
      {
        EXPECT_EQ(newPolygons.size(), 2);
      }
      catch (const exception& exception)
      {
        FAIL();
      }

      try
      {
        EXPECT_EQ(newPolygons[0].getNumberVertices() , 5);
        EXPECT_EQ(newPolygons[1].getNumberVertices(), 3);
      }
      catch (const exception& exception)
      {
        FAIL();
      }

    }

  TEST(TestIntersectorPolygonLine, FindPolygons5b) //TEST FACILE2 - square, endpoints inside
    {
      vector<Point> polygonVertices;
      polygonVertices.resize(4);

      polygonVertices[0] = Point(0, 0);
      polygonVertices[1] = Point(4, 0);
      polygonVertices[2] = Point(4, 4);
      polygonVertices[3] = Point(0, 4);


      Polygon polygon(polygonVertices);

      Point end(3.03, 3.63);
      Point start(3.48, 3.03);
      Segment segment(start, end);

      Intersector1D1D intersector1d1d;
      IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
      vector<Point> intersectionPoints = intersector.findIntersectionVertices();
      vector<Polygon> newPolygons = intersector.findPolygons();
      vector<Point> newPoints = intersector.findNewPoints();
      vector<Polygon> newExtendedPolygons = intersector.getExtendedPolygons();

      try
      {
        EXPECT_EQ(newPolygons.size(), 2);
      }
      catch (const exception& exception)
      {
        FAIL();
      }

      try
      {
        EXPECT_EQ(newPolygons[0].getNumberVertices() , 5);
        EXPECT_EQ(newPolygons[1].getNumberVertices(), 3);
      }
      catch (const exception& exception)
      {
        FAIL();
      }

    }

  TEST(TestIntersectorPolygonLine, FindPolygons5c) //TEST FACILE3 - square, one endpoint inside, one outside
    {
      vector<Point> polygonVertices;
      polygonVertices.resize(4);

      polygonVertices[0] = Point(0, 0);
      polygonVertices[1] = Point(4, 0);
      polygonVertices[2] = Point(4, 4);
      polygonVertices[3] = Point(0, 4);


      Polygon polygon(polygonVertices);

      Point start(3.03, 3.63);
      Point end(2, 5);
      Segment segment(start, end);

      Intersector1D1D intersector1d1d;
      IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
      vector<Point> intersectionPoints = intersector.findIntersectionVertices();
      vector<Polygon> newPolygons = intersector.findPolygons();
      vector<Point> newPoints = intersector.findNewPoints();
      vector<Polygon> newExtendedPolygons = intersector.getExtendedPolygons();

      try
      {
        EXPECT_EQ(newPolygons.size(), 2);
      }
      catch (const exception& exception)
      {
        FAIL();
      }

      try
      {
        EXPECT_EQ(newPolygons[0].getNumberVertices() , 5);
        EXPECT_EQ(newPolygons[1].getNumberVertices(), 3);
      }
      catch (const exception& exception)
      {
        FAIL();
      }

    }

  TEST(TestIntersectorPolygonLine, FindPolygons5d) //TEST FACILE4 - square, one endpoint inside, one outside
    {
      vector<Point> polygonVertices;
      polygonVertices.resize(4);

      polygonVertices[0] = Point(0, 0);
      polygonVertices[1] = Point(4, 0);
      polygonVertices[2] = Point(4, 4);
      polygonVertices[3] = Point(0, 4);


      Polygon polygon(polygonVertices);

      Point start(3.48, 3.03);
      Point end(5, 1);
      Segment segment(start, end);

      Intersector1D1D intersector1d1d;
      IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
      vector<Point> intersectionPoints = intersector.findIntersectionVertices();
      vector<Polygon> newPolygons = intersector.findPolygons();
      vector<Point> newPoints = intersector.findNewPoints();
      vector<Polygon> newExtendedPolygons = intersector.getExtendedPolygons();

      try
      {
        EXPECT_EQ(newPolygons.size(), 2);
      }
      catch (const exception& exception)
      {
        FAIL();
      }

      try
      {
        EXPECT_EQ(newPolygons[0].getNumberVertices() , 5);
        EXPECT_EQ(newPolygons[1].getNumberVertices(), 3);
      }
      catch (const exception& exception)
      {
        FAIL();
      }

    }

  TEST(TestIntersectorPolygonLine, FindPolygons6) // rettangolo
    {
      vector<Point> polygonVertices;
      polygonVertices.resize(4);

      polygonVertices[0] = Point(1, 1);
      polygonVertices[1] = Point(5, 1);
      polygonVertices[2] = Point(5, 3.1);
      polygonVertices[3] = Point(1, 3.1);

      Polygon polygon(polygonVertices);


      Point start(2, 1.2);
      Point end(4, 3);
      Segment segment(start, end);
      Intersector1D1D intersector1d1d;
      IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
      vector<Point> intersectionPoints = intersector.findIntersectionVertices();
      vector<Polygon> newPolygons = intersector.findPolygons();
      vector<Point> newPoints = intersector.findNewPoints();
      vector<Polygon> newExtendedPolygons = intersector.getExtendedPolygons();
      try
      {
        EXPECT_EQ(newPolygons.size(), 2);
      }
      catch (const exception& exception)
      {
        FAIL();
      }

      try
      {
        EXPECT_EQ(newPolygons[0].getNumberVertices() , 4);
        EXPECT_EQ(newPolygons[1].getNumberVertices(), 4);
        EXPECT_EQ(newExtendedPolygons[0].getNumberVertices(), 6);
        EXPECT_EQ(newExtendedPolygons[1].getNumberVertices(), 6);

      }
      catch (const exception& exception)
      {
        FAIL();
      }

      try
      {
      //Polygon 0-6-4-5-7-3
      EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(0), 0);
      EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(1), 6);
      EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(2), 4);
      EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(3), 5);
      EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(4), 7);
      EXPECT_EQ(newExtendedPolygons[0].getVertexLabelAtPosition(5), 3);
      //Polygon 1-2-7-5-4-6
      EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(0), 1);
      EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(1), 2);
      EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(2), 7);
      EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(3), 5);
      EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(4), 4);
      EXPECT_EQ(newExtendedPolygons[1].getVertexLabelAtPosition(5), 6);

      }
      catch (const exception& exception)
      {
        FAIL();
      }

    }


  TEST(TestIntersectorPolygonLine, FindPolygons7)
  {
    vector<Point> polygonVertices;
    polygonVertices.resize(10);

    polygonVertices[0] = Point(2, -2);
    polygonVertices[1] = Point(0, -1);
    polygonVertices[2] = Point(3, 1);
    polygonVertices[3] = Point(0, 2);
    polygonVertices[4] = Point(3, 2);
    polygonVertices[5] = Point(3, 3);
    polygonVertices[6] = Point(-1, 3);
    polygonVertices[7] = Point(-3, 1);
    polygonVertices[8] = Point(0, 0);
    polygonVertices[9] = Point(-3, -2);

    Polygon polygon(polygonVertices);

    Point start(-4, -4);
    Point end(4, 4);
    Segment segment(start, end);

    Intersector1D1D intersector1d1d;
    IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
    vector<Point> intersectionPoints = intersector.findIntersectionVertices();
    vector<Polygon> newPolygons = intersector.findPolygons();
    vector<Point> newPoints = intersector.findNewPoints();
    vector<Polygon> newExtendedPolygons = intersector.getExtendedPolygons();

    try
    {
      EXPECT_EQ(newPolygons.size(), 4);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    try
    {
      EXPECT_EQ(newPolygons[0].getNumberVertices(), 6);
      EXPECT_EQ(newPolygons[1].getNumberVertices(), 7);
      EXPECT_EQ(newPolygons[2].getNumberVertices(), 3);
      EXPECT_EQ(newPolygons[3].getNumberVertices(), 3);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

  }


  TEST(TestIntersectorPolygonLine, FindPolygons7b)
  {
    vector<Point> polygonVertices;
    polygonVertices.resize(10);

    polygonVertices[0] = Point(2, -2);
    polygonVertices[1] = Point(0, -1);
    polygonVertices[2] = Point(3, 1);
    polygonVertices[3] = Point(0, 2);
    polygonVertices[4] = Point(3, 2);
    polygonVertices[5] = Point(3, 3);
    polygonVertices[6] = Point(-1, 3);
    polygonVertices[7] = Point(-3, 1);
    polygonVertices[8] = Point(0, 0);
    polygonVertices[9] = Point(-3, -2);

    Polygon polygon(polygonVertices);

    Point start(0, -3);
    Point end(0, 4);
    Segment segment(start, end);

    Intersector1D1D intersector1d1d;
    IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
    vector<Point> intersectionPoints = intersector.findIntersectionVertices();
    vector<Polygon> newPolygons = intersector.findPolygons();
    vector<Point> newPoints = intersector.findNewPoints();
    vector<Polygon> newExtendedPolygons = intersector.getExtendedPolygons();

    try
    {
      EXPECT_EQ(newPolygons.size(), 5);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    try
    {
      EXPECT_EQ(newPolygons[0].getNumberVertices(), 3);
      EXPECT_EQ(newPolygons[1].getNumberVertices(), 4);
      EXPECT_EQ(newPolygons[2].getNumberVertices(), 4);
      EXPECT_EQ(newPolygons[3].getNumberVertices(), 5);
      EXPECT_EQ(newPolygons[4].getNumberVertices(), 4);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

  }

  TEST(TestIntersectorPolygonLine, CutPolygonOnEdge)
  {
    vector<Point> polygonVertices;
    polygonVertices.resize(10);

    polygonVertices[0] = Point(0, 2);
    polygonVertices[1] = Point(1, 1);
    polygonVertices[2] = Point(2, 2);
    polygonVertices[3] = Point(3, 0);
    polygonVertices[4] = Point(4, 0);
    polygonVertices[5] = Point(5, 2);
    polygonVertices[6] = Point(6, 2);
    polygonVertices[7] = Point(6, 3);
    polygonVertices[8] = Point(3, 4);
    polygonVertices[9] = Point(0, 3);

    Polygon polygon(polygonVertices);

    Point start(0, 0);
    Point end(6, 0);
    Segment segment(start, end);

    Intersector1D1D intersector1d1d;
    IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
    vector<Point> intersectionPoints = intersector.findIntersectionVertices();
    vector<Polygon> newPolygons = intersector.findPolygons();
    vector<Point> newPoints = intersector.findNewPoints();
    vector<Polygon> newExtendedPolygons = intersector.getExtendedPolygons();

    try
    {
      EXPECT_EQ(newPolygons.size(), 1);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    try
    {
      EXPECT_EQ(newPolygons[0].getNumberVertices(), 10);

    }
    catch (const exception& exception)
    {
      FAIL();
    }

  }

  TEST(TestIntersectorPolygonLine, CutPolygonOnEdge2)
  {
    vector<Point> polygonVertices;
    polygonVertices.resize(10);

    polygonVertices[0] = Point(0, 2);
    polygonVertices[1] = Point(1, 1);
    polygonVertices[2] = Point(2, 2);
    polygonVertices[3] = Point(3, 0);
    polygonVertices[4] = Point(4, 0);
    polygonVertices[5] = Point(5, 2);
    polygonVertices[6] = Point(6, 2);
    polygonVertices[7] = Point(6, 3);
    polygonVertices[8] = Point(3, 4);
    polygonVertices[9] = Point(0, 3);

    Polygon polygon(polygonVertices);

    Point start(3.5, 0);
    Point end(3.8, 0);
    Segment segment(start, end);

    Intersector1D1D intersector1d1d;
    IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
    vector<Point> intersectionPoints = intersector.findIntersectionVertices();
    vector<Polygon> newPolygons = intersector.findPolygons();
    vector<Point> newPoints = intersector.findNewPoints();
    vector<Polygon> newExtendedPolygons = intersector.getExtendedPolygons();

    try
    {
      EXPECT_EQ(newPolygons.size(), 1);
      EXPECT_EQ(newExtendedPolygons.size(), 1);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    try
    {
      EXPECT_EQ(newPolygons[0].getNumberVertices(), 10);
      EXPECT_EQ(newExtendedPolygons[0].getNumberVertices(), 12);

    }
    catch (const exception& exception)
    {
      FAIL();
    }

  }

  TEST(TestIntersectorPolygonLine, CutPolygonOnEdge3)
  {
    vector<Point> polygonVertices;
    polygonVertices.resize(4);

    polygonVertices[0] = Point(0, 0);
    polygonVertices[1] = Point(1, 0);
    polygonVertices[2] = Point(1, 1);
    polygonVertices[3] = Point(0, 1);


    Polygon polygon(polygonVertices);

    Point start(-1, 0);
    Point end(0.5, 0);
    Segment segment(start, end);

    Intersector1D1D intersector1d1d;
    IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
    vector<Point> intersectionPoints = intersector.findIntersectionVertices();
    vector<Polygon> newPolygons = intersector.findPolygons();
    vector<Point> newPoints = intersector.findNewPoints();
    vector<Polygon> newExtendedPolygons = intersector.getExtendedPolygons();

    try
    {
      EXPECT_EQ(newPolygons.size(), 1);
      EXPECT_EQ(newExtendedPolygons.size(), 1);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    try
    {
      EXPECT_EQ(newPolygons[0].getNumberVertices(), 4);
      EXPECT_EQ(newExtendedPolygons[0].getNumberVertices(), 5);

    }
    catch (const exception& exception)
    {
      FAIL();
    }

  }

  TEST(TestIntersectorPolygonLine, CutPolygonOnEdge4)
  {
    vector<Point> polygonVertices;
    polygonVertices.resize(8);

    polygonVertices[0] = Point(0, 0);
    polygonVertices[1] = Point(1, 0);
    polygonVertices[2] = Point(1, 1);
    polygonVertices[3] = Point(2, 1);
    polygonVertices[4] = Point(2, 0);
    polygonVertices[5] = Point(3, 0);
    polygonVertices[6] = Point(3, 2);
    polygonVertices[7] = Point(0, 2);


    Polygon polygon(polygonVertices);

    Point start(1.5, 0);
    Point end(2.5, 0);
    Segment segment(start, end);

    Intersector1D1D intersector1d1d;
    IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);
    vector<Point> intersectionPoints = intersector.findIntersectionVertices();
    vector<Polygon> newPolygons = intersector.findPolygons();
    vector<Point> newPoints = intersector.findNewPoints();
    vector<Polygon> newExtendedPolygons = intersector.getExtendedPolygons();

    try
    {
      EXPECT_EQ(newPolygons.size(), 1);
      EXPECT_EQ(newExtendedPolygons.size(), 1);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    try
    {
      EXPECT_EQ(newPolygons[0].getNumberVertices(), 8);
      EXPECT_EQ(newExtendedPolygons[0].getNumberVertices(), 9);

    }
    catch (const exception& exception)
    {
      FAIL();
    }

  }

}


namespace IntersectorPolygonLineNamespace{
TEST(TestIntersectorPolygonLine, TestCheckInConicCombination)
{
  vector<Point> polygonVertices;
  polygonVertices.resize(5);

  polygonVertices[0] = Point(0, 0);
  polygonVertices[1] = Point(4, 0);
  polygonVertices[2] = Point(2, 2);
  polygonVertices[3] = Point(4, 4);
  polygonVertices[4] = Point(0, 4);


  Polygon polygon(polygonVertices);

  Point start(1, 0);
  Point end(3, 4);
  Segment segment(start, end);
  Vector2d vect = segment.getTangent();
  Vector2d v1(-2,2);
  Vector2d v2(2,2);
  int flag = -2;

  Intersector1D1D intersector1d1d;
  IntersectorPolygonLine intersector(intersector1d1d, polygon, segment);

  try
  {
    EXPECT_EQ(intersector.checkInConicCombination(vect, v1, v2, flag), true);
    EXPECT_EQ(flag, 1);
  }
  catch (const exception& exception)
  {
    FAIL();
  }

  Point start2(3, 4);
  Point end2(1, 0);
  Segment segment2(start2, end2);
  Vector2d vect2 = segment2.getTangent();
  int flag2 = -2;

  try
  {
    EXPECT_EQ(intersector.checkInConicCombination(vect2, v1, v2, flag2), true);
    EXPECT_EQ(flag2, -1);
  }
  catch (const exception& exception)
  {
    FAIL();
  }

  Point start3(0, 1);
  Point end3(4, 3);
  Segment segment3(start3, end3);
  Vector2d vect3 = segment3.getTangent();
  int flag3 = -2;

  try
  {
    EXPECT_EQ(intersector.checkInConicCombination(vect3, v1, v2, flag3), false);
    EXPECT_EQ(flag3, 0);
  }
  catch (const exception& exception)
  {
    FAIL();
  }

}

}
#endif


