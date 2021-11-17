#ifndef __TEST_POLYGONCUTTER_H
#define __TEST_POLYGONCUTTER_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>

#include "PolygonCutter.hpp"

using namespace PolygonCutterNamespace;

using namespace testing;
using namespace std;

namespace PolygonCutterTesting {

class MockIntersectorPolygonLine : public IIntersectorPolygonLine {
  private:
    MOCK_CONST_METHOD4(checkInConicCombination, bool(const Vector2d &line, const Vector2d &v1, const Vector2d &v2, int &flag));
    MOCK_METHOD4(extendPolygonIfEndpointsOnEdge, void(int &numPoly, const int &firstIntersectionId, const int &secondIntersectionId, const bool &forwardDirection));

  public:
    MOCK_METHOD0(findIntersectionVertices, const vector<Point>&());
    MOCK_METHOD0(findPolygons, const vector<Polygon>&());

    MOCK_METHOD0(getExtendedPolygons, const vector<Polygon>&());
    MOCK_METHOD0(findNewPoints, const vector<Point>&());

    MOCK_CONST_METHOD0(getStartFound, bool());
    MOCK_CONST_METHOD0(getEndFound, bool());
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

TEST(TestPolygonCutter, CutPolygon7)
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

  Point start(-4, -4);
  Point end(4, 4);
  Segment segment(start, end);

  vector<Point> intersectionPoints;
  intersectionPoints.resize(6);
  intersectionPoints[0] = Point(-2, -2);
  intersectionPoints[1] = Point(0, 0);
  intersectionPoints[2] = Point(0, 0);
  intersectionPoints[3] = Point(1.5, 1.5);
  intersectionPoints[4] = Point(2, 2);
  intersectionPoints[5] = Point(3, 3);

  vector<Polygon> cuttedPolygons;
  cuttedPolygons.resize(4);

  cuttedPolygons[0].appendVertex(Point(2, -2));
  cuttedPolygons[0].appendVertex(Point(0, -1));
  cuttedPolygons[0].appendVertex(Point(3, 1));
  cuttedPolygons[0].appendVertex(Point(1.5, 1.5));
  cuttedPolygons[0].appendVertex(Point(0, 0));
  cuttedPolygons[0].appendVertex(Point(-2, -2));

  cuttedPolygons[1].appendVertex(Point(0, 2));
  cuttedPolygons[1].appendVertex(Point(2, 2));
  cuttedPolygons[1].appendVertex(Point(3, 3));
  cuttedPolygons[1].appendVertex(Point(-1, 3));
  cuttedPolygons[1].appendVertex(Point(-3, 1));
  cuttedPolygons[1].appendVertex(Point(0, 0));
  cuttedPolygons[1].appendVertex(Point(1.5, 1.5));

  cuttedPolygons[2].appendVertex(Point(3, 2));
  cuttedPolygons[2].appendVertex(Point(3, 3));
  cuttedPolygons[2].appendVertex(Point(2, 2));

  cuttedPolygons[3].appendVertex(Point(-3, -2));
  cuttedPolygons[3].appendVertex(Point(-2, -2));
  cuttedPolygons[3].appendVertex(Point(0, 0));

  vector<Point> newPoints;

  MockIntersectorPolygonLine intersector;
  MockPolygon polygon;
  PolygonCutter polygonCutter(intersector, polygon, segment);

  EXPECT_CALL(intersector, findIntersectionVertices)
          .WillOnce(ReturnRef(intersectionPoints));
  // on_call perchè non ci interessa il suo test
  ON_CALL(intersector, findNewPoints)
          .WillByDefault(ReturnRef(newPoints));
  EXPECT_CALL(intersector, findPolygons)
          .WillOnce(ReturnRef(cuttedPolygons));
  EXPECT_CALL(polygon, getVertices)
          .WillOnce(ReturnRef(polygonVertices));

  polygonCutter.cutPolygon();
  const vector<Polygon>& newPolygons = polygonCutter.getCuttedPolygons();

  polygonCutter.showPolygon("showPolygon7.m");

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

}

#endif
