#ifndef __TEST_POLYGONCLASS_H
#define __TEST_POLYGONCLASS_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>

#include "Polygon.hpp"

using namespace testing;
using namespace std;

namespace PolygonTesting {

  TEST(TestPolygonClass, SetterGetterMethods)
  {
    Point p0(1, 2);
    Point p1(3, 2);
    Point p2(2, 6);

    vector<Point> vertices;
    vertices.resize(3);
    vertices[0] = p0;
    vertices[1] = p1;
    vertices[2] = p2;

    vector<Segment> edges;
    edges.resize(3);
    edges[0] = Segment(p0, p1);
    edges[1] = Segment(p1, p2);
    edges[2] = Segment(p2, p0);

    Polygon poly1( vertices);
    Polygon poly2;
    try
    {
      EXPECT_EQ(poly1.getNumberVertices(), 3);
      EXPECT_EQ(poly2.getNumberVertices(), 0);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    Point p00(1, 2);
    Point p11(3, 2);
    Point p22(2, 6);
    poly2.appendVertex(p00);
    poly2.appendVertex(p11);
    poly2.appendVertex(p22);

    try
    {
      EXPECT_EQ(poly1.getVertices(), vertices);

    }
    catch (const exception& exception)
    {
      FAIL();
    }

    //Testing getVertices
    try
    {
      EXPECT_EQ(poly1.getVertices(), vertices);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    //Testing setVertexAtPosition

    Point p3(3.5, 2.3);
    Point p4(2.2, 3.4);
    Point p5(2.5, 3.4);

    poly1.setVertexAtPosition(p3, 2);
    poly1.setVertexAtPosition(p4, 1);
    poly1.setVertexAtPosition(p5, 0);
    try
    {
      EXPECT_EQ(poly1.getVertices()[2], p3);
      EXPECT_EQ(poly1.getVertices()[1], p4);
      EXPECT_EQ(poly1.getVertices()[0], p5);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    //Testing getVertexAtPosition, getLastVertex
    try
    {
      EXPECT_EQ(poly1.getVertexAtPosition(2), p3);
      EXPECT_EQ(poly1.getVertexAtPosition(1), p4);
      EXPECT_EQ(poly1.getVertexAtPosition(0), p5);
      EXPECT_EQ(poly1.getLastVertex(), p3);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    //Testing getEdges
    try
    {
      EXPECT_EQ(poly1.getEdges(), edges);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    //testing nextVertexId

    int id = 3;
    try
    {
      poly1.nextVertexId(id);
    }
    catch (const exception& exception)
    {
      EXPECT_EQ("Error: Vertex id is not present", std::string(exception.what()));
    }

    id = 2;
    try
    {
      EXPECT_EQ(poly1.nextVertexId(id), 0);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

    id = 0;

    try
    {
      EXPECT_EQ(poly1.nextVertexId(id), 1);
    }
    catch (const exception& exception)
    {
      FAIL();
    }

  }

  TEST(TestPolygonClass, InsertionMethods)
  {
      //Testing appendVertex
      vector<Point> vertices;
      vertices.resize(3);
      Point p0(1,2);
      Point p1(3,2);
      Point p2(2,6);

      vertices[0] = p0;
      vertices[1] = p1;
      vertices[2] = p2;

      Polygon poly1( vertices);
      Point p3(1.5,3.8);
      poly1.appendVertex(p3);
      try
      {
        EXPECT_EQ(poly1.getVertices()[3], p3);
        EXPECT_EQ(poly1.getNumberVertices(), 4);
      }
      catch (const exception& exception)
      {
        FAIL();
      }

      //Testing insertVertexAtPosition
      Point p4(2.2,1.8);
      poly1.insertVertexAtPosition(p4,1);
      try
      {
        EXPECT_EQ(poly1.getVertices()[0], p0);
        EXPECT_EQ(poly1.getVertices()[1], p4);
        EXPECT_EQ(poly1.getVertices()[2], p1);
        EXPECT_EQ(poly1.getVertices()[3], p2);
        EXPECT_EQ(poly1.getVertices()[4], p3);
        EXPECT_EQ(poly1.getNumberVertices(), 5);
      }
      catch (const exception& exception)
      {
        FAIL();
      }
  }


  TEST(TestPolygonClass, TestLabelMethods)
  {
      Point p0(1, 2);
      Point p1(3, 2);
      Point p2(2, 6);

      vector<Point> vertices;
      vertices.resize(3);
      vertices[0] = p0;
      vertices[1] = p1;
      vertices[2] = p2;

      Polygon poly(vertices);

      try
      {
        poly.setDefaultVertexLabels();
        EXPECT_EQ(0, poly.getVertexAtPosition(0).getPointLabel());
        EXPECT_EQ(1, poly.getVertexAtPosition(1).getPointLabel());
        EXPECT_EQ(2, poly.getVertexAtPosition(2).getPointLabel());
      }
      catch (const exception& exception)
      {
        FAIL();
      }

      try
      {
        poly.setVertexLabelAtPosition(0, 1);
        EXPECT_EQ(1, poly.getVertexLabelAtPosition(0));
      }
      catch (const exception& exception)
      {
        FAIL();
      }

      vector<unsigned int> vector;
      vector.push_back(3);
      vector.push_back(5);
      vector.push_back(7);
      try
      {
        poly.setVertexLabels(vector);
        EXPECT_EQ(3, poly.getVertexAtPosition(0).getPointLabel());
        EXPECT_EQ(5, poly.getVertexAtPosition(1).getPointLabel());
        EXPECT_EQ(7, poly.getVertexAtPosition(2).getPointLabel());
      }
      catch (const exception& exception)
      {
        FAIL();
      }

  }

  TEST(TestPolygonClass, AreaMethod)
  {
      Point p0(0,0);
      Point p1(4,0);
      Point p2(4,4);
      Point p3(0,4);

      vector<Point> vertices;
      vertices.resize(4);
      vertices[0] = p0;
      vertices[1] = p1;
      vertices[2] = p2;
      vertices[3] = p3;

      Polygon polygon(vertices);


      try
      {
        EXPECT_FLOAT_EQ(16, polygon.ComputeArea());
      }
      catch (const exception& exception)
      {
        FAIL();
      }

      Point p4(1,2);
      Point p5(2,0);
      polygon.insertVertexAtPosition(p4, 1);
      polygon.insertVertexAtPosition(p5, 2);

      try
      {
        EXPECT_FLOAT_EQ(14, polygon.ComputeArea());
      }
      catch (const exception& exception)
      {
        FAIL();
      }

      Point p6(3,7);
      Point p7(2,4);
      Point p8(1,9);

      polygon.insertVertexAtPosition(p6, 5);
      polygon.insertVertexAtPosition(p7, 6);
      polygon.insertVertexAtPosition(p8, 7);

      try
      {
        EXPECT_FLOAT_EQ(22, polygon.ComputeArea());
      }
      catch (const exception& exception)
      {
        FAIL();
      }

  }

  TEST(TestPolygonClass, TestPointInPolygon)
  {
      vector<Point> polygonVertices;
      polygonVertices.resize(5);

      polygonVertices[0] = Point(2.5, 1.0);
      polygonVertices[1] = Point(4.0, 2.1);
      polygonVertices[2] = Point(3.4, 4.2);
      polygonVertices[3] = Point(1.6, 4.2);
      polygonVertices[4] = Point(1.0, 2.1);

      Polygon polygon(polygonVertices);

       Point test1(2.0,2.0);
       Point test2(2.5,6.0);
       Point test3(5.0,2.0);


       try {

            EXPECT_TRUE(polygon.pointInPolygon(test1));
            EXPECT_FALSE(polygon.pointInPolygon(test2));
            EXPECT_FALSE(polygon.pointInPolygon(test3));

            }
        catch (const exception& ex)
        {
          FAIL();
        }
  }

  TEST(TestPolygonClass, TestIsPolygonOnTheRightSide)
  {
      vector<Point> polygon1Vertices;
      vector<Point> polygon2Vertices;
      polygon1Vertices.resize(3);
      polygon2Vertices.resize(3);

      polygon1Vertices[0] = Point(1, 0);
      polygon1Vertices[1] = Point(4, 0);
      polygon1Vertices[2] = Point(3, 4);

      polygon2Vertices[0] = Point(4, 0);
      polygon2Vertices[1] = Point(6, 0);
      polygon2Vertices[2] = Point(5, 4);

      Polygon polygon1(polygon1Vertices);
      Polygon polygon2(polygon2Vertices);

      Point start1(3, -1);
      Point end1(3, 4);
      Point start2(4, -1);
      Point end2(4, 5);
      Point start4(0, 0);
      Point end4(3, 0);
      Point start5(0, 0);
      Point end5(1.5, 2);

      Segment line1(start1, end1);
      Segment line2(start2, end2);
      Segment line3(end1, start1);
      Segment line4(start4, end4);
      Segment line5(end4, start4);
      Segment line6(start5, end5);
      Segment line7(end5, start5);


       try {
            EXPECT_EQ(polygon1.isPolygonOnTheRightSide(line1), 0);
            EXPECT_EQ(polygon1.isPolygonOnTheRightSide(line2), -1);
            EXPECT_EQ(polygon2.isPolygonOnTheRightSide(line1), 1);
            EXPECT_EQ(polygon2.isPolygonOnTheRightSide(line2), 1);
            EXPECT_EQ(polygon1.isPolygonOnTheRightSide(line3), 0);
            EXPECT_EQ(polygon2.isPolygonOnTheRightSide(line3), -1);
            EXPECT_EQ(polygon1.isPolygonOnTheRightSide(line4), -1);
            EXPECT_EQ(polygon2.isPolygonOnTheRightSide(line4), -1);
            EXPECT_EQ(polygon1.isPolygonOnTheRightSide(line5), 1);
            EXPECT_EQ(polygon2.isPolygonOnTheRightSide(line5), 1);
            EXPECT_EQ(polygon1.isPolygonOnTheRightSide(line6), 1);
            EXPECT_EQ(polygon2.isPolygonOnTheRightSide(line6), 1);
            EXPECT_EQ(polygon1.isPolygonOnTheRightSide(line7), -1);
            EXPECT_EQ(polygon2.isPolygonOnTheRightSide(line7), -1);

            }
        catch (const exception& ex)
        {
          FAIL();
        }
  }

  TEST(TestPolygonClass, TestBuildUpPolygon)
  {
      Polygon poly;
      Point p0(0,2);
      Point p1(1,0);
      Point p2(4,3);
      Point p3(3,4);

      poly.appendVertex(p0);
      poly.appendVertex(p1);
      poly.appendVertex(p2);
      poly.appendVertex(p3);


       try {
            EXPECT_EQ(poly.getEdges().size(), 0);
            poly.buildUpPolygonEdges();
            EXPECT_EQ(poly.getEdges().size(), 4);

            }
        catch (const exception& ex)
        {
          FAIL();
        }
  }

}

#endif // __TEST_POLYGONCLASS_H

