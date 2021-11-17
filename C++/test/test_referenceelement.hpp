#ifndef __TEST_REFERENCEELEMENTCLASS_H
#define __TEST_REFERENCEELEMENTCLASS_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>
#include "iostream"

#include "IntersectorPolygonLine.hpp"
#include "ReferenceElement.hpp"

using namespace IntersectorPolygonLineNamespace;
using namespace testing;
using namespace std;
using namespace ReferenceElementNamespace;

namespace ReferenceElementTesting {

   TEST(TestReferenceElementClass, ComputeBoundingBox)
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

       Point firstReferenceElementPoint = Point(Vector2d(-3, -2));
       Point secondReferenceElementPoint =Point(Vector2d(3, -2));
       Point thirdReferenceElementPoint = Point(Vector2d(3, 3));
       Point fourthReferenceElementPoint = Point(Vector2d(-3, 3));

       Polygon polygon = Polygon(polygonVertices);
       ReferenceElement element;
       element.computeBoundingBox(polygon);

       try {
           EXPECT_EQ(firstReferenceElementPoint, element.getBoundingBoxVertices()[0]);
           EXPECT_EQ(secondReferenceElementPoint, element.getBoundingBoxVertices()[1]);
           EXPECT_EQ(thirdReferenceElementPoint,element.getBoundingBoxVertices()[2]);
           EXPECT_EQ(fourthReferenceElementPoint, element.getBoundingBoxVertices()[3]);

       }
       catch (const exception&)
       {
           FAIL();
       }

   }

   TEST(TestReferenceElementClass, ComputeReferenceElement1) //Con il Poligono di D'Auria
   {
       vector<Point> polygonVertices, vector1, vector2, vector3;
       Point p0, p1, p2, p3, p4, p5, p6, p7, p8, p9;
       polygonVertices.resize(10);
       ReferenceElement referenceElement;

       p0 = Point(2, -2);
       p1 = Point(0, -1);
       p2 = Point(3, 1);
       p3 = Point(0, 2);
       p4 = Point(3, 2);
       p5 = Point(3, 3);
       p6 = Point(-1, 3);
       p7 = Point(-3, 1);
       p8 = Point(0, 0);
       p9 = Point(-3, -2);

       polygonVertices[0] = p0;
       polygonVertices[1] = p1;
       polygonVertices[2] = p2;
       polygonVertices[3] = p3;
       polygonVertices[4] = p4;
       polygonVertices[5] = p5;
       polygonVertices[6] = p6;
       polygonVertices[7] = p7;
       polygonVertices[8] = p8;
       polygonVertices[9] = p9;

       Polygon polygon = Polygon(polygonVertices);

       referenceElement.computeBoundingBox(polygon);
       referenceElement.computeReferenceElement(polygon);

       referenceElement.showReferenceElement("showReferenceElement7.m");

       try {
           EXPECT_EQ(referenceElement.getBoundingBoxVertices()[1], referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(0));
           EXPECT_EQ(p2, referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(1));
           EXPECT_EQ(p1, referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(2));
           EXPECT_EQ(p0, referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(3));
           EXPECT_EQ(p4, referenceElement.getReferenceElementPolygons()[2].getVertexAtPosition(0));
           EXPECT_EQ(p3, referenceElement.getReferenceElementPolygons()[2].getVertexAtPosition(1));
           EXPECT_EQ(p2, referenceElement.getReferenceElementPolygons()[2].getVertexAtPosition(2));
           EXPECT_EQ(referenceElement.getBoundingBoxVertices()[3], referenceElement.getReferenceElementPolygons()[3].getVertexAtPosition(0));
           EXPECT_EQ(p7, referenceElement.getReferenceElementPolygons()[3].getVertexAtPosition(1));
           EXPECT_EQ(p6, referenceElement.getReferenceElementPolygons()[3].getVertexAtPosition(2));
           EXPECT_EQ(referenceElement.getBoundingBoxVertices()[0], referenceElement.getReferenceElementPolygons()[4].getVertexAtPosition(0));
           EXPECT_EQ(p8, referenceElement.getReferenceElementPolygons()[4].getVertexAtPosition(1));
           EXPECT_EQ(p7, referenceElement.getReferenceElementPolygons()[4].getVertexAtPosition(2));
           EXPECT_EQ(5, referenceElement.getReferenceElementPolygons().size());


       }
       catch (const exception& ex)
       {
        FAIL();
       }
   }

       TEST(TestReferenceElementClass, ComputeReferenceElement2)
       {
           vector<Point> polygonVertices;
           Point p0, p1, p2, p3, p4, p5;
           polygonVertices.resize(6);
           ReferenceElement referenceElement;

           p0 = Point(1.5, 1.0);
           p1 = Point(5.6, 1.5);
           p2 = Point(5.5, 4.8);
           p3 = Point(4.0, 6.2);
           p4 = Point(3.2, 4.2);
           p5 = Point(1.0, 4.0);

           polygonVertices[0] = p0;
           polygonVertices[1] = p1;
           polygonVertices[2] = p2;
           polygonVertices[3] = p3;
           polygonVertices[4] = p4;
           polygonVertices[5] = p5;

           Polygon polygon = Polygon(polygonVertices);

           referenceElement.computeBoundingBox(polygon);
           referenceElement.computeReferenceElement(polygon);

           try {

               EXPECT_EQ(5, referenceElement.getReferenceElementPolygons().size());
               EXPECT_EQ(referenceElement.getBoundingBoxVertices()[1], referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(0));
               EXPECT_EQ(p1, referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(1));
               EXPECT_EQ(p0, referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(2));
               EXPECT_EQ(referenceElement.getBoundingBoxVertices()[2], referenceElement.getReferenceElementPolygons()[2].getVertexAtPosition(0));
               EXPECT_EQ(p3, referenceElement.getReferenceElementPolygons()[2].getVertexAtPosition(1));
               EXPECT_EQ(p2, referenceElement.getReferenceElementPolygons()[2].getVertexAtPosition(2));
               EXPECT_EQ(p1, referenceElement.getReferenceElementPolygons()[2].getVertexAtPosition(3));
               EXPECT_EQ(referenceElement.getBoundingBoxVertices()[3], referenceElement.getReferenceElementPolygons()[3].getVertexAtPosition(0));
               EXPECT_EQ(p5, referenceElement.getReferenceElementPolygons()[3].getVertexAtPosition(1));
               EXPECT_EQ(p4, referenceElement.getReferenceElementPolygons()[3].getVertexAtPosition(2));
               EXPECT_EQ(p3, referenceElement.getReferenceElementPolygons()[3].getVertexAtPosition(3));
               EXPECT_EQ(referenceElement.getBoundingBoxVertices()[0], referenceElement.getReferenceElementPolygons()[4].getVertexAtPosition(0));
               EXPECT_EQ(p0, referenceElement.getReferenceElementPolygons()[4].getVertexAtPosition(1));
               EXPECT_EQ(p5, referenceElement.getReferenceElementPolygons()[4].getVertexAtPosition(2));


              }
           catch (const exception& ex)
           {
            FAIL();
          }
      }

       TEST(TestReferenceElementClass, ComputeReferenceElement3)
       {
           vector<Point> polygonVertices;
           Point p0, p1, p2, p3;
           polygonVertices.resize(4);
           ReferenceElement referenceElement;

           p0 = Point(0, 0);
           p1 = Point(4, 0);
           p2 = Point(4, 4);
           p3 = Point(0, 4);

           polygonVertices[0] = Point(0, 0);
           polygonVertices[1] = Point(4, 0);
           polygonVertices[2] = Point(4, 4);
           polygonVertices[3] = Point(0, 4);

           Polygon polygon = Polygon(polygonVertices);

           referenceElement.computeBoundingBox(polygon);
           referenceElement.computeReferenceElement(polygon);

           try {

               EXPECT_EQ(1, referenceElement.getReferenceElementPolygons().size());

              }
           catch (const exception& ex)
           {
            FAIL();
          }

       }

       TEST(TestReferenceElementClass, ComputeReferenceElement4)
       {
           vector<Point> polygonVertices;
           Point p0, p1, p2, p3, p4;
           polygonVertices.resize(5);
           ReferenceElement referenceElement;

           p0 = Point(2.5, 1.0);
           p1 = Point(4.0, 2.1);
           p2 = Point(3.4, 4.2);
           p3 = Point(1.6, 4.2);
           p4 = Point(1.0, 2.1);

           polygonVertices[0] = p0;
           polygonVertices[1] = p1;
           polygonVertices[2] = p2;
           polygonVertices[3] = p3;
           polygonVertices[4] = p4;

           Polygon polygon = Polygon(polygonVertices);

           referenceElement.computeBoundingBox(polygon);
           referenceElement.computeReferenceElement(polygon);

           try {

               EXPECT_EQ(5, referenceElement.getReferenceElementPolygons().size());
               EXPECT_EQ(referenceElement.getBoundingBoxVertices()[1], referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(0));
               EXPECT_EQ(p1, referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(1));
               EXPECT_EQ(p0, referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(2));
               EXPECT_EQ(referenceElement.getBoundingBoxVertices()[2], referenceElement.getReferenceElementPolygons()[2].getVertexAtPosition(0));
               EXPECT_EQ(p2, referenceElement.getReferenceElementPolygons()[2].getVertexAtPosition(1));
               EXPECT_EQ(p1, referenceElement.getReferenceElementPolygons()[2].getVertexAtPosition(2));
               EXPECT_EQ(referenceElement.getBoundingBoxVertices()[3], referenceElement.getReferenceElementPolygons()[3].getVertexAtPosition(0));
               EXPECT_EQ(p4, referenceElement.getReferenceElementPolygons()[3].getVertexAtPosition(1));
               EXPECT_EQ(p3, referenceElement.getReferenceElementPolygons()[3].getVertexAtPosition(2));
               EXPECT_EQ(referenceElement.getBoundingBoxVertices()[0], referenceElement.getReferenceElementPolygons()[4].getVertexAtPosition(0));
               EXPECT_EQ(p0, referenceElement.getReferenceElementPolygons()[4].getVertexAtPosition(1));
               EXPECT_EQ(p4, referenceElement.getReferenceElementPolygons()[4].getVertexAtPosition(2));

              }
           catch (const exception& ex)
           {
            FAIL();
          }

       }

       TEST(TestReferenceElementClass, ComputeReferenceElement5)
       {
           vector<Point> polygonVertices;
           Point p0, p1, p2, p3, p4, p5, p6, p7;
           polygonVertices.resize(8);
           ReferenceElement referenceElement;

           p0 = Point(0, 0);
           p1 = Point(8, 0);
           p2 = Point(4.64, 1.5);
           p3 = Point(8.93, 4.48);
           p4 = Point(2.18, 5.36);
           p5 = Point(5.52, 9.22);
           p6 = Point(0, 5);
           p7 = Point(6, 4);

           polygonVertices[0] = Point(0, 0);
           polygonVertices[1] = Point(8, 0);
           polygonVertices[2] = Point(4.64, 1.5);
           polygonVertices[3] = Point(8.93, 4.48);
           polygonVertices[4] = Point(2.18, 5.36);
           polygonVertices[5] = Point(5.52, 9.22);
           polygonVertices[6] = Point(0, 5);
           polygonVertices[7] = Point(6, 4);

           Polygon polygon = Polygon(polygonVertices);

           referenceElement.computeBoundingBox(polygon);
           referenceElement.computeReferenceElement(polygon);

           try {

               EXPECT_EQ(5, referenceElement.getReferenceElementPolygons().size());
               EXPECT_EQ(referenceElement.getBoundingBoxVertices()[1], referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(0));
               EXPECT_EQ(p3, referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(1));
               EXPECT_EQ(p2, referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(2));
               EXPECT_EQ(p1, referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(3));
               EXPECT_EQ(referenceElement.getBoundingBoxVertices()[2], referenceElement.getReferenceElementPolygons()[2].getVertexAtPosition(0));
               EXPECT_EQ(p5, referenceElement.getReferenceElementPolygons()[2].getVertexAtPosition(1));
               EXPECT_EQ(p4, referenceElement.getReferenceElementPolygons()[2].getVertexAtPosition(2));
               EXPECT_EQ(p3, referenceElement.getReferenceElementPolygons()[2].getVertexAtPosition(3));
               EXPECT_EQ(referenceElement.getBoundingBoxVertices()[3], referenceElement.getReferenceElementPolygons()[3].getVertexAtPosition(0));
               EXPECT_EQ(p6, referenceElement.getReferenceElementPolygons()[3].getVertexAtPosition(1));
               EXPECT_EQ(p5, referenceElement.getReferenceElementPolygons()[3].getVertexAtPosition(2));
               EXPECT_EQ(referenceElement.getBoundingBoxVertices()[0], referenceElement.getReferenceElementPolygons()[4].getVertexAtPosition(0));
               EXPECT_EQ(p7, referenceElement.getReferenceElementPolygons()[4].getVertexAtPosition(1));
               EXPECT_EQ(p6, referenceElement.getReferenceElementPolygons()[4].getVertexAtPosition(2));

              }
           catch (const exception& ex)
           {
            FAIL();
          }

       }

       TEST(TestReferenceElementClass, ComputeReferenceElement6)
       {
           vector<Point> polygonVertices;
           Point p0, p1, p2;
           polygonVertices.resize(3);
           ReferenceElement referenceElement;

           p0 = Point(0, 0);
           p1 = Point(1, 0);
           p2 = Point(1,1);

           polygonVertices[0] = p0;
           polygonVertices[1] = p1;
           polygonVertices[2] = p2;

           Polygon polygon = Polygon(polygonVertices);

           referenceElement.computeBoundingBox(polygon);
           referenceElement.computeReferenceElement(polygon);

           try {

               EXPECT_EQ(2, referenceElement.getReferenceElementPolygons().size());
               EXPECT_EQ(referenceElement.getBoundingBoxVertices()[3], referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(0));
               EXPECT_EQ(p0, referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(1));
               EXPECT_EQ(p2, referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(2));

              }
           catch (const exception& ex)
           {
            FAIL();
          }

       }

       TEST(TestReferenceElementClass, ComputeReferenceElement8)
       {
           vector<Point> polygonVertices;
           Point p0, p1, p2;
           polygonVertices.resize(3);
           ReferenceElement referenceElement;

           p0 = Point(0, 0);
           p1 = Point(1, 0);
           p2 = Point(0, 1);

           polygonVertices[0] = p0;
           polygonVertices[1] = p1;
           polygonVertices[2] = p2;

           Polygon polygon = Polygon(polygonVertices);

           referenceElement.computeBoundingBox(polygon);
           referenceElement.computeReferenceElement(polygon);

           try {

               EXPECT_EQ(2, referenceElement.getReferenceElementPolygons().size());
               EXPECT_EQ(referenceElement.getBoundingBoxVertices()[2], referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(0));
               EXPECT_EQ(p2, referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(1));
               EXPECT_EQ(p1, referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(2));

              }
           catch (const exception& ex)
           {
            FAIL();
          }

       }

       TEST(TestReferenceElementClass, ComputeReferenceElement9)
       {
           vector<Point> polygonVertices;
           Point p0, p1, p2;
           polygonVertices.resize(3);
           ReferenceElement referenceElement;

           p0 = Point(1, 1);
           p1 = Point(0, 1);
           p2 = Point(0.5, 0);

           polygonVertices[0] = p0;
           polygonVertices[1] = p1;
           polygonVertices[2] = p2;

           Polygon polygon = Polygon(polygonVertices);

           referenceElement.computeBoundingBox(polygon);
           referenceElement.computeReferenceElement(polygon);

           try {

               EXPECT_EQ(3, referenceElement.getReferenceElementPolygons().size());
               EXPECT_EQ(referenceElement.getBoundingBoxVertices()[1], referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(0));
               EXPECT_EQ(referenceElement.getBoundingBoxVertices()[2], referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(1));
               EXPECT_EQ(p2, referenceElement.getReferenceElementPolygons()[1].getVertexAtPosition(2));
               EXPECT_EQ(referenceElement.getBoundingBoxVertices()[0], referenceElement.getReferenceElementPolygons()[2].getVertexAtPosition(0));
               EXPECT_EQ(p2, referenceElement.getReferenceElementPolygons()[2].getVertexAtPosition(1));
               EXPECT_EQ(referenceElement.getBoundingBoxVertices()[3], referenceElement.getReferenceElementPolygons()[2].getVertexAtPosition(2));


              }
           catch (const exception& ex)
           {
            FAIL();
          }

       }

       TEST(TestReferenceElementClass, findBoundaryPoints)
       {
           vector<Point> polygonVertices;
           Point p0, p1, p2, p3;
           polygonVertices.resize(4);
           ReferenceElement referenceElement;

           p0 = Point(0, 2);
           p1 = Point(1, 0);
           p2 = Point(4, 3);
           p3 = Point(3, 4);

           polygonVertices[0] = p0;
           polygonVertices[1] = p1;
           polygonVertices[2] = p2;
           polygonVertices[3] = p3;

           Polygon polygon = Polygon(polygonVertices);

           referenceElement.computeBoundingBox(polygon);
           referenceElement.computeReferenceElement(polygon);
           referenceElement.findBoundaryVertices();

           try {

               EXPECT_EQ(5, referenceElement.getReferenceElementPolygons().size());
               EXPECT_EQ(1, referenceElement.getMapSouthXCoordinates().size());
               EXPECT_EQ(1, referenceElement.getMapNorthXCoordinates().size());
               EXPECT_EQ(1, referenceElement.getMapEastYCoordinates().size());
               EXPECT_EQ(1, referenceElement.getMapWestYCoordinates().size());
               map<double, Point>::const_iterator it ;
               it = referenceElement.getMapSouthXCoordinates().begin();
               EXPECT_EQ(p1, it->second);
               EXPECT_EQ(p1.getCoordinates().x(), it->first);
               it = referenceElement.getMapNorthXCoordinates().begin();
               EXPECT_EQ(p3, it->second);
               EXPECT_EQ(p3.getCoordinates().x(), it->first);
               it = referenceElement.getMapEastYCoordinates().begin();
               EXPECT_EQ(p2, it->second);
               EXPECT_EQ(p2.getCoordinates().y(), it->first);
               it = referenceElement.getMapWestYCoordinates().begin();
               EXPECT_EQ(p0, it->second);
               EXPECT_EQ(p0.getCoordinates().y(), it->first);
              }
           catch (const exception& ex)
           {
            FAIL();
          }

       }

       TEST(TestReferenceElementClass, findBoundaryPoints2)
       {
           vector<Point> polygonVertices;
           Point p0, p1, p2, p3, p4, p5, p6, p7, p8;
           polygonVertices.resize(9);
           ReferenceElement referenceElement;

           p0 = Point(0, 0);
           p1 = Point(1, 2);
           p2 = Point(2, 0);
           p3 = Point(3, 2);
           p4 = Point(4, 0);
           p5 = Point(5, 0);
           p6 = Point(5, 3);
           p7 = Point(2.5, 4);
           p8 = Point(0, 3);

           polygonVertices[0] = p0;
           polygonVertices[1] = p1;
           polygonVertices[2] = p2;
           polygonVertices[3] = p3;
           polygonVertices[4] = p4;
           polygonVertices[5] = p5;
           polygonVertices[6] = p6;
           polygonVertices[7] = p7;
           polygonVertices[8] = p8;

           Polygon polygon = Polygon(polygonVertices);

           referenceElement.computeBoundingBox(polygon);
           referenceElement.computeReferenceElement(polygon);
           referenceElement.findBoundaryVertices();

           try {

               EXPECT_EQ(5, referenceElement.getReferenceElementPolygons().size());
               EXPECT_EQ(2, referenceElement.getMapSouthXCoordinates().size());
               EXPECT_EQ(1, referenceElement.getMapNorthXCoordinates().size());
               EXPECT_EQ(1, referenceElement.getMapEastYCoordinates().size());
               EXPECT_EQ(1, referenceElement.getMapWestYCoordinates().size());
               map<double, Point>::const_iterator it ;
               it = referenceElement.getMapSouthXCoordinates().begin();
               EXPECT_EQ(p2, it->second);
               EXPECT_EQ(2, it->first);
               it++;
               EXPECT_EQ(p4, it->second);
               EXPECT_EQ(4, it->first);
               it = referenceElement.getMapNorthXCoordinates().begin();
               EXPECT_EQ(p7, it->second);
               EXPECT_EQ(2.5, it->first);
               it = referenceElement.getMapEastYCoordinates().begin();
               EXPECT_EQ(p6, it->second);
               EXPECT_EQ(3, it->first);
               it = referenceElement.getMapWestYCoordinates().begin();
               EXPECT_EQ(p8, it->second);
               EXPECT_EQ(3, it->first);
              }
           catch (const exception& ex)
           {
            FAIL();
          }

       }

       TEST(TestReferenceElementClass, MakeConforming)//quadrilatero
       {
           vector<Point> polygonVertices;
           Point p0, p1, p2, p3;
           polygonVertices.resize(4);
           ReferenceElement referenceElement;

           p0 = Point(0, 2);
           p1 = Point(1, 0);
           p2 = Point(4, 3);
           p3 = Point(3, 4);

           polygonVertices[0] = p0;
           polygonVertices[1] = p1;
           polygonVertices[2] = p2;
           polygonVertices[3] = p3;

           Polygon polygon = Polygon(polygonVertices);

           referenceElement.computeBoundingBox(polygon);
           referenceElement.computeReferenceElement(polygon);
           referenceElement.findBoundaryVertices();
           referenceElement.makeConforming();

           try {

               EXPECT_EQ(5, referenceElement.getConformingReferenceElementPolygons().size());
               EXPECT_EQ(4, referenceElement.getConformingReferenceElementPolygons()[0].getNumberVertices());
               EXPECT_EQ(5, referenceElement.getConformingReferenceElementPolygons()[1].getNumberVertices());
               EXPECT_EQ(3, referenceElement.getConformingReferenceElementPolygons()[2].getNumberVertices());
               EXPECT_EQ(5, referenceElement.getConformingReferenceElementPolygons()[3].getNumberVertices());
               EXPECT_EQ(3, referenceElement.getConformingReferenceElementPolygons()[4].getNumberVertices());
              }
           catch (const exception& ex)
           {
            FAIL();
           }

       }

       TEST(TestReferenceElementClass, MakeConforming2a)
       {
           vector<Point> polygonVertices;
           Point p0, p1, p2, p3, p4, p5, p6, p7, p8;
           polygonVertices.resize(9);
           ReferenceElement referenceElement;

           p0 = Point(0, 0);
           p1 = Point(1, 2);
           p2 = Point(2, 0);
           p3 = Point(3, 2);
           p4 = Point(4, 0);
           p5 = Point(5, 0);
           p6 = Point(5, 3);
           p7 = Point(2.5, 4);
           p8 = Point(0, 3);

           polygonVertices[0] = p0;
           polygonVertices[1] = p1;
           polygonVertices[2] = p2;
           polygonVertices[3] = p3;
           polygonVertices[4] = p4;
           polygonVertices[5] = p5;
           polygonVertices[6] = p6;
           polygonVertices[7] = p7;
           polygonVertices[8] = p8;

           Polygon polygon = Polygon(polygonVertices);

           referenceElement.computeBoundingBox(polygon);
           referenceElement.computeReferenceElement(polygon);
           referenceElement.findBoundaryVertices();
           referenceElement.makeConforming();

           try {
               EXPECT_EQ(5, referenceElement.getConformingReferenceElementPolygons().size());
               EXPECT_EQ(9, referenceElement.getConformingReferenceElementPolygons()[0].getNumberVertices());
               EXPECT_EQ(3, referenceElement.getConformingReferenceElementPolygons()[1].getNumberVertices());
               EXPECT_EQ(4, referenceElement.getConformingReferenceElementPolygons()[2].getNumberVertices());
               EXPECT_EQ(4, referenceElement.getConformingReferenceElementPolygons()[3].getNumberVertices());
               EXPECT_EQ(4, referenceElement.getConformingReferenceElementPolygons()[4].getNumberVertices());

              }
           catch (const exception& ex)
           {
            FAIL();
           }

       }

       TEST(TestReferenceElementClass, MakeConforming2b)
       {
           vector<Point> polygonVertices;
           Point p0, p1, p2, p3, p4, p5, p6, p7, p8;
           polygonVertices.resize(9);
           ReferenceElement referenceElement;

           p0 = Point(0, 0);
           p1 = Point(1, 2);
           p2 = Point(2, 0);
           p3 = Point(3, 2);
           p4 = Point(4, 0);
           p5 = Point(5, 0);
           p6 = Point(5, 3);
           p7 = Point(2, 4);
           p8 = Point(0, 3);

           polygonVertices[0] = p0;
           polygonVertices[1] = p1;
           polygonVertices[2] = p2;
           polygonVertices[3] = p3;
           polygonVertices[4] = p4;
           polygonVertices[5] = p5;
           polygonVertices[6] = p6;
           polygonVertices[7] = p7;
           polygonVertices[8] = p8;

           Polygon polygon = Polygon(polygonVertices);

           referenceElement.computeBoundingBox(polygon);
           referenceElement.computeReferenceElement(polygon);
           referenceElement.findBoundaryVertices();
           referenceElement.makeConforming();

           try {
               EXPECT_EQ(5, referenceElement.getConformingReferenceElementPolygons().size());
               EXPECT_EQ(9, referenceElement.getConformingReferenceElementPolygons()[0].getNumberVertices());
               EXPECT_EQ(3, referenceElement.getConformingReferenceElementPolygons()[1].getNumberVertices());
               EXPECT_EQ(3, referenceElement.getConformingReferenceElementPolygons()[2].getNumberVertices());
               EXPECT_EQ(4, referenceElement.getConformingReferenceElementPolygons()[3].getNumberVertices());
               EXPECT_EQ(3, referenceElement.getConformingReferenceElementPolygons()[4].getNumberVertices());
              }
           catch (const exception& ex)
           {
            FAIL();
           }
       }

       TEST(TestReferenceElementClass, MakeConforming3)//con il Poligono di D'Auria
       {
           vector<Point> polygonVertices, vector1, vector2, vector3;
           Point p0, p1, p2, p3, p4, p5, p6, p7, p8, p9;
           polygonVertices.resize(10);
           ReferenceElement referenceElement;

           p0 = Point(2, -2);
           p1 = Point(0, -1);
           p2 = Point(3, 1);
           p3 = Point(0, 2);
           p4 = Point(3, 2);
           p5 = Point(3, 3);
           p6 = Point(-1, 3);
           p7 = Point(-3, 1);
           p8 = Point(0, 0);
           p9 = Point(-3, -2);

           polygonVertices[0] = p0;
           polygonVertices[1] = p1;
           polygonVertices[2] = p2;
           polygonVertices[3] = p3;
           polygonVertices[4] = p4;
           polygonVertices[5] = p5;
           polygonVertices[6] = p6;
           polygonVertices[7] = p7;
           polygonVertices[8] = p8;
           polygonVertices[9] = p9;

           Polygon polygon = Polygon(polygonVertices);

           referenceElement.computeBoundingBox(polygon);
           referenceElement.computeReferenceElement(polygon);
           referenceElement.findBoundaryVertices();
           referenceElement.makeConforming();


           try {
               EXPECT_EQ(5, referenceElement.getConformingReferenceElementPolygons().size());
               EXPECT_EQ(12, referenceElement.getConformingReferenceElementPolygons()[0].getNumberVertices());
               EXPECT_EQ(4, referenceElement.getConformingReferenceElementPolygons()[1].getNumberVertices());
               EXPECT_EQ(3, referenceElement.getConformingReferenceElementPolygons()[2].getNumberVertices());
               EXPECT_EQ(4, referenceElement.getConformingReferenceElementPolygons()[3].getNumberVertices());
               EXPECT_EQ(3, referenceElement.getConformingReferenceElementPolygons()[4].getNumberVertices());
           }
           catch (const exception& ex)
           {
            FAIL();
           }
       }
}

#endif
