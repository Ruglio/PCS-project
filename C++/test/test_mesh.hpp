#ifndef __TEST_MESHCLASS_H
#define __TEST_MESHCLASS_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>
#include "iostream"

#include "IntersectorPolygonLine.hpp"
#include "ReferenceElement.hpp" //eliminare quello che non serva
#include "Mesh.hpp"

using namespace testing;
using namespace std;
using namespace ReferenceElementNamespace;
using namespace MeshNamespace;
using namespace IntersectorPolygonLineNamespace;//eliminare quello che non serva



namespace MeshTesting {
   TEST(TestMeshClass, TestMeshConstructor)
   {

       vector<Point> polygonVertices;
       polygonVertices.resize(4);

       polygonVertices[0] = Point(0, 2);
       polygonVertices[1] = Point(1, 0);
       polygonVertices[2] = Point(4, 3);
       polygonVertices[3] = Point(3, 4);

       Polygon basePolygon(polygonVertices);
       Mesh myMesh(basePolygon);

       try
       {
           double BoundingBoxLength = myMesh.getBoundingBoxLength();
           double BoundingBoxHeight = myMesh.getBoundingBoxHeight();
           EXPECT_EQ(myMesh.getBoundingBoxLength(), 4);
           EXPECT_EQ(myMesh.getBoundingBoxHeight(), 4);
           myMesh.setRectangularDomain(4*BoundingBoxLength + 1, 3*BoundingBoxHeight+1);
           EXPECT_EQ(myMesh.getDomainBoundingBoxLength(), 17);
           EXPECT_EQ(myMesh.getDomainBoundingBoxHeight(), 13);
           EXPECT_EQ(myMesh.getDomain().getEdges()[0].getTangent().norm(), 17);
           EXPECT_EQ(myMesh.getDomain().getEdges()[1].getTangent().norm(), 13);
           EXPECT_EQ(myMesh.getDomain().getEdges()[2].getTangent().norm(), 17);
           EXPECT_EQ(myMesh.getDomain().getEdges()[3].getTangent().norm(), 13);
           EXPECT_EQ(myMesh.getDomainBoundingBoxHeight(), 13);

           EXPECT_EQ(myMesh.getMaxNumRefElementsPerRow(), 5);
           EXPECT_EQ(myMesh.getMaxNumRefElementsPerColumn(), 4);

       }
       catch (const exception& ex)
       {
         FAIL();
       }

   }

   TEST(TestMeshClass, TestReferenceElementInConvexDomain)
   {
       ReferenceElement referenceElement;
       Mesh mesh = Mesh();

       vector<Point> polygonVertices;
       polygonVertices.resize(5);

       polygonVertices[0] = Point(2.5, 1.0);
       polygonVertices[1] = Point(4.0, 2.1);
       polygonVertices[2] = Point(3.4, 4.2);
       polygonVertices[3] = Point(1.6, 4.2);
       polygonVertices[4] = Point(1.0, 2.1);

       Polygon polygon(polygonVertices);

       referenceElement.computeReferenceElement(polygon);

       try {

            EXPECT_TRUE(mesh.referenceElementInConvexDomain(referenceElement));

            }
        catch (const exception& ex)
        {
          FAIL();
        }
  }

   TEST(TestMeshClass, TestReferenceElementInConvexDomain2)
   {
       ReferenceElement referenceElement;


       vector<Point> polygonVertices;
       polygonVertices.resize(4);

       polygonVertices[0] = Point(0, 0);
       polygonVertices[1] = Point(4, 0);
       polygonVertices[2] = Point(4, 4);
       polygonVertices[3] = Point(0, 4);

       Polygon polygon(polygonVertices);

       Mesh mesh = Mesh(polygon);
       mesh.setRectangularDomain(8,8);

       try {

            EXPECT_TRUE(mesh.referenceElementInConvexDomain(mesh.getReferenceElement()));

            }
        catch (const exception& ex)
        {
          FAIL();
        }
  }

   TEST(TestMeshClass, TestTranslatePolygon)
   {
       Mesh myMesh;
       vector<Point> polygonVertices;
       polygonVertices.resize(4);

       polygonVertices[0] = Point(0, 2);
       polygonVertices[1] = Point(1, 0);
       polygonVertices[2] = Point(4, 3);
       polygonVertices[3] = Point(3, 4);

       Polygon polygon(polygonVertices);

       Point translatedPoint0= Point(7, 7);
       Point translatedPoint1 = Point(8, 5);
       Point translatedPoint2 = Point(11, 8);
       Point translatedPoint3 = Point(10, 9);

       try {
            Polygon translatedPolygonByUsingTranslatePolygon = myMesh.TranslatePolygon(polygon, 7 , 5);

            EXPECT_EQ( translatedPoint0, translatedPolygonByUsingTranslatePolygon.getVertexAtPosition(0));
            EXPECT_EQ( translatedPoint1, translatedPolygonByUsingTranslatePolygon.getVertexAtPosition(1));
            EXPECT_EQ( translatedPoint2, translatedPolygonByUsingTranslatePolygon.getVertexAtPosition(2));
            EXPECT_EQ( translatedPoint3, translatedPolygonByUsingTranslatePolygon.getVertexAtPosition(3));
            }
        catch (const exception& ex)
        {
          FAIL();
        }
  }

   TEST(TestMeshClass, TestTranslateReferenceElement)
   {

       vector<Point> polygonVertices;
       polygonVertices.resize(4);

       polygonVertices[0] = Point(0, 2);
       polygonVertices[1] = Point(1, 0);
       polygonVertices[2] = Point(4, 3);
       polygonVertices[3] = Point(3, 4);
       Polygon polygon(polygonVertices);

       Mesh myMesh(polygon);

       Point translatedPoint0= Point(7, 7);
       Point translatedPoint1 = Point(8, 5);
       Point translatedPoint2 = Point(11, 8);
       Point translatedPoint3 = Point(10, 9);

       Point translatedPointA= Point(7, 5);
       Point translatedPointB= Point(11, 5);
       Point translatedPointC= Point(11, 9);
       Point translatedPointD= Point(7, 9);

       Point translatedPointW= Point(7, 8);
       Point translatedPointS= Point(10, 5);
       Point translatedPointE= Point(11, 7);
       Point translatedPointN= Point(8, 9);

       try {
            ReferenceElement translatedReferenceElement = myMesh.TranslateConformingReferenceElement(7,5);
            EXPECT_EQ( translatedReferenceElement.getConformingReferenceElementPolygons().size(), 5);
            EXPECT_EQ( translatedReferenceElement.getConformingReferenceElementPolygons()[0].getEdges().size(), 4);
            EXPECT_EQ( translatedReferenceElement.getConformingReferenceElementPolygons()[1].getEdges().size(), 5);
            EXPECT_EQ( translatedReferenceElement.getConformingReferenceElementPolygons()[2].getEdges().size(), 3);
            EXPECT_EQ( translatedReferenceElement.getConformingReferenceElementPolygons()[3].getEdges().size(), 5);
            EXPECT_EQ( translatedReferenceElement.getConformingReferenceElementPolygons()[4].getEdges().size(), 3);

            EXPECT_EQ( translatedPoint0, translatedReferenceElement.getConformingReferenceElementPolygons()[0].getVertexAtPosition(0));
            EXPECT_EQ( translatedPoint1, translatedReferenceElement.getConformingReferenceElementPolygons()[0].getVertexAtPosition(1));
            EXPECT_EQ( translatedPoint2, translatedReferenceElement.getConformingReferenceElementPolygons()[0].getVertexAtPosition(2));
            EXPECT_EQ( translatedPoint3, translatedReferenceElement.getConformingReferenceElementPolygons()[0].getVertexAtPosition(3));

            EXPECT_EQ( translatedPointS, translatedReferenceElement.getConformingReferenceElementPolygons()[1].getVertexAtPosition(0));
            EXPECT_EQ( translatedPointB, translatedReferenceElement.getConformingReferenceElementPolygons()[1].getVertexAtPosition(1));
            EXPECT_EQ( translatedPointE, translatedReferenceElement.getConformingReferenceElementPolygons()[1].getVertexAtPosition(2));
            EXPECT_EQ( translatedPoint2, translatedReferenceElement.getConformingReferenceElementPolygons()[1].getVertexAtPosition(3));
            EXPECT_EQ( translatedPoint1, translatedReferenceElement.getConformingReferenceElementPolygons()[1].getVertexAtPosition(4));

            EXPECT_EQ( translatedPointC, translatedReferenceElement.getConformingReferenceElementPolygons()[2].getVertexAtPosition(0));
            EXPECT_EQ( translatedPoint3, translatedReferenceElement.getConformingReferenceElementPolygons()[2].getVertexAtPosition(1));
            EXPECT_EQ( translatedPoint2, translatedReferenceElement.getConformingReferenceElementPolygons()[2].getVertexAtPosition(2));

            EXPECT_EQ( translatedPointN, translatedReferenceElement.getConformingReferenceElementPolygons()[3].getVertexAtPosition(0));
            EXPECT_EQ( translatedPointD, translatedReferenceElement.getConformingReferenceElementPolygons()[3].getVertexAtPosition(1));
            EXPECT_EQ( translatedPointW, translatedReferenceElement.getConformingReferenceElementPolygons()[3].getVertexAtPosition(2));
            EXPECT_EQ( translatedPoint0, translatedReferenceElement.getConformingReferenceElementPolygons()[3].getVertexAtPosition(3));
            EXPECT_EQ( translatedPoint3, translatedReferenceElement.getConformingReferenceElementPolygons()[3].getVertexAtPosition(4));

            EXPECT_EQ( translatedPointA, translatedReferenceElement.getConformingReferenceElementPolygons()[4].getVertexAtPosition(0));
            EXPECT_EQ( translatedPoint1, translatedReferenceElement.getConformingReferenceElementPolygons()[4].getVertexAtPosition(1));
            EXPECT_EQ( translatedPoint0, translatedReferenceElement.getConformingReferenceElementPolygons()[4].getVertexAtPosition(2));

            EXPECT_EQ( translatedPointA, translatedReferenceElement.getBoundingBox().getVertexAtPosition(0));
            EXPECT_EQ( translatedPointB, translatedReferenceElement.getBoundingBox().getVertexAtPosition(1));
            EXPECT_EQ( translatedPointC, translatedReferenceElement.getBoundingBox().getVertexAtPosition(2));
            EXPECT_EQ( translatedPointD, translatedReferenceElement.getBoundingBox().getVertexAtPosition(3));
            EXPECT_EQ( translatedReferenceElement.getBoundingBox().getEdges().size(), 4);

            }
        catch (const exception& ex)
        {
          FAIL();
        }
  }

   TEST(TestMeshClass, TestCutAndDiscardPolygonsOnRighSide)
   {
       Mesh myMesh;
       vector<Point> polygonVertices;
       polygonVertices.resize(4);

       polygonVertices[0] = Point(0, 2);
       polygonVertices[1] = Point(1, 0);
       polygonVertices[2] = Point(4, 3);
       polygonVertices[3] = Point(3, 4);

       Point start1(1, -1);
       Point end1(1, 5);
       Segment line1(start1, end1);
       Point start2(0, 1);
       Point end2(5, 1);
       Segment line2(start2, end2);

       Point start3(0, 4);
       Point end3(1, 1);
       Segment line3(start3, end3);

       Polygon polygon(polygonVertices);


       try {
           ReferenceElement refElem;
           refElem.computeBoundingBox(polygon);
           refElem.computeReferenceElement( polygon);
           refElem.findBoundaryVertices();
           refElem.makeConforming();

           vector<Polygon> vectorPolygons;
           vectorPolygons = refElem.getConformingReferenceElementPolygons();
           EXPECT_EQ( vectorPolygons.size(), 5);

           //vertical cut
           vector<Polygon> vectorPolygonsAfterCutAndDiscard;
           myMesh.cutAndDiscardPolygonsOnRightSide(refElem, line1);
           vectorPolygonsAfterCutAndDiscard = refElem.getConformingReferenceElementPolygons();
           EXPECT_EQ( vectorPolygonsAfterCutAndDiscard.size(), 3);
           EXPECT_EQ( vectorPolygonsAfterCutAndDiscard[0].getNumberVertices(), 3);
           EXPECT_EQ( vectorPolygonsAfterCutAndDiscard[1].getNumberVertices(), 5);
           EXPECT_EQ( vectorPolygonsAfterCutAndDiscard[2].getNumberVertices(), 3);
           EXPECT_EQ(vectorPolygonsAfterCutAndDiscard[0].ComputeArea() + vectorPolygonsAfterCutAndDiscard[1].ComputeArea()
                   + vectorPolygonsAfterCutAndDiscard[2].ComputeArea(), 4  );

           //horizontal cut after the previous cut
           vector<Polygon> vectorPolygonsAfterCutAndDiscard2;
           myMesh.cutAndDiscardPolygonsOnRightSide(refElem, line2);
           vectorPolygonsAfterCutAndDiscard2 = refElem.getConformingReferenceElementPolygons();
           EXPECT_EQ( vectorPolygonsAfterCutAndDiscard2.size(), 3);
           EXPECT_EQ( vectorPolygonsAfterCutAndDiscard2[0].getNumberVertices(), 4);
           EXPECT_EQ( vectorPolygonsAfterCutAndDiscard2[1].getNumberVertices(), 5);
           EXPECT_EQ( vectorPolygonsAfterCutAndDiscard2[2].getNumberVertices(), 3);
           EXPECT_EQ(vectorPolygonsAfterCutAndDiscard2[0].ComputeArea() + vectorPolygonsAfterCutAndDiscard2[1].ComputeArea()
                   + vectorPolygonsAfterCutAndDiscard2[2].ComputeArea(), 3  );

           //slanted cut after previous cut
           vector<Polygon> vectorPolygonsAfterCutAndDiscard3;
           myMesh.cutAndDiscardPolygonsOnRightSide(refElem, line3);
           vectorPolygonsAfterCutAndDiscard3 = refElem.getConformingReferenceElementPolygons();
           EXPECT_EQ( vectorPolygonsAfterCutAndDiscard3.size(), 2);
           EXPECT_EQ( vectorPolygonsAfterCutAndDiscard3[0].getNumberVertices(), 3);
           EXPECT_EQ( vectorPolygonsAfterCutAndDiscard3[1].getNumberVertices(), 4);
           EXPECT_EQ(vectorPolygonsAfterCutAndDiscard3[0].ComputeArea() + vectorPolygonsAfterCutAndDiscard3[1].ComputeArea(), 1.5  );

       }
        catch (const exception& ex)
        {
          FAIL();
        }


  }

   TEST(TestMeshClass, TestCreateMesh_RectangularDomain)
   {
       //for  rectangular mesh of (4+1)x(3+1) reference elements
       // the base polygon is a quadrilateral

       vector<Point> polygonVertices;
       polygonVertices.resize(4);

       polygonVertices[0] = Point(0, 2);
       polygonVertices[1] = Point(1, 0);
       polygonVertices[2] = Point(4, 3);
       polygonVertices[3] = Point(3, 4);

       Polygon basePolygon(polygonVertices);
       Mesh myMesh(basePolygon);

       double BoundingBoxLength = myMesh.getBoundingBoxLength();
       double BoundingBoxHeight = myMesh.getBoundingBoxHeight();
       myMesh.setRectangularDomain(4*BoundingBoxLength + 1, 3*BoundingBoxHeight+1);

       try
       {
       myMesh.createMesh();
       vector<ReferenceElement> myMeshCells = myMesh.getMeshCells();

       myMesh.showMesh();

       EXPECT_EQ(myMeshCells.size(),20);
       EXPECT_EQ(myMeshCells[0].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[1].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[2].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[3].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[4].getConformingReferenceElementPolygons().size(), 3);

       EXPECT_EQ(myMeshCells[5].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[6].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[7].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[8].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[9].getConformingReferenceElementPolygons().size(), 3);

       EXPECT_EQ(myMeshCells[10].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[11].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[12].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[13].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[14].getConformingReferenceElementPolygons().size(), 3);

       EXPECT_EQ(myMeshCells[15].getConformingReferenceElementPolygons().size(), 3);
       EXPECT_EQ(myMeshCells[16].getConformingReferenceElementPolygons().size(), 3);
       EXPECT_EQ(myMeshCells[17].getConformingReferenceElementPolygons().size(), 3);
       EXPECT_EQ(myMeshCells[18].getConformingReferenceElementPolygons().size(), 3);
       EXPECT_EQ(myMeshCells[19].getConformingReferenceElementPolygons().size(), 2);

       double totalArea = 0;
       double domainArea = myMesh.getDomain().ComputeArea();
       for(unsigned int i = 0; i < myMeshCells.size(); i++)
           for (unsigned int j = 0; j < myMeshCells[i].getConformingReferenceElementPolygons().size(); j++)
                  totalArea += myMeshCells[i].getConformingReferenceElementPolygons()[j].ComputeArea();

       EXPECT_DOUBLE_EQ(totalArea, domainArea);

       }
       catch (const exception& ex)
       {
         FAIL();
       }


   }

   TEST(TestMeshClass, TestCreateMesh_RectangularDomain2)
   {
       //for  rectangular mesh of (4+1)x(3+1) reference elements
       // the base polygon is the concave hexagon from project 1

       vector<Point> polygonVertices;
       polygonVertices.resize(6);

       polygonVertices[0] = Point(1.5, 1.0);
       polygonVertices[1] = Point(5.6, 1.5);
       polygonVertices[2] = Point(5.5, 4.8);
       polygonVertices[3] = Point(4.0, 6.2);
       polygonVertices[4] = Point(3.2, 4.2);
       polygonVertices[5] = Point(1.0, 4.0);

       Polygon basePolygon(polygonVertices);
       Mesh myMesh(basePolygon);

       double BoundingBoxLength = myMesh.getBoundingBoxLength();
       double BoundingBoxHeight = myMesh.getBoundingBoxHeight();
       myMesh.setRectangularDomain(4*BoundingBoxLength + 1, 3*BoundingBoxHeight+1);

       try
       {
       myMesh.createMesh();
       vector<ReferenceElement> myMeshCells = myMesh.getMeshCells();

       myMesh.showMesh("showMesh2.m");

       EXPECT_EQ(myMeshCells.size(),20);
       EXPECT_EQ(myMeshCells[0].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[1].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[2].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[3].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[4].getConformingReferenceElementPolygons().size(), 4);

       EXPECT_EQ(myMeshCells[5].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[6].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[7].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[8].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[9].getConformingReferenceElementPolygons().size(), 4);

       EXPECT_EQ(myMeshCells[10].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[11].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[12].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[13].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[14].getConformingReferenceElementPolygons().size(), 4);

       EXPECT_EQ(myMeshCells[15].getConformingReferenceElementPolygons().size(), 4);
       EXPECT_EQ(myMeshCells[16].getConformingReferenceElementPolygons().size(), 4);
       EXPECT_EQ(myMeshCells[17].getConformingReferenceElementPolygons().size(), 4);
       EXPECT_EQ(myMeshCells[18].getConformingReferenceElementPolygons().size(), 4);
       EXPECT_EQ(myMeshCells[19].getConformingReferenceElementPolygons().size(), 3);

       double totalArea = 0;
       double domainArea = myMesh.getDomain().ComputeArea();
       for(unsigned int i = 0; i < myMeshCells.size(); i++)
           for (unsigned int j = 0; j < myMeshCells[i].getConformingReferenceElementPolygons().size(); j++)
                  totalArea += myMeshCells[i].getConformingReferenceElementPolygons()[j].ComputeArea();

       EXPECT_DOUBLE_EQ(totalArea, domainArea);
       }
       catch (const exception& ex)
       {
         FAIL();
       }

   }

   TEST(TestMeshClass, TestCreateMesh_RectangularDomain3)
   {
       //for  rectangular mesh of (4+1)x(3+1) reference elements
       //the base polygon is D'Auria's polygon with the shape of a sigma

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

       Polygon basePolygon(polygonVertices);
       Mesh myMesh(basePolygon);

       double BoundingBoxLength = myMesh.getBoundingBoxLength();
       double BoundingBoxHeight = myMesh.getBoundingBoxHeight();
       myMesh.setRectangularDomain(4*BoundingBoxLength + 1, 3*BoundingBoxHeight+1);

       try
       {
       myMesh.createMesh();
       vector<ReferenceElement> myMeshCells = myMesh.getMeshCells();

       myMesh.showMesh("showMesh3.m");

       EXPECT_EQ(myMeshCells.size(),20);
       EXPECT_EQ(myMeshCells[0].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[1].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[2].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[3].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[4].getConformingReferenceElementPolygons().size(), 4);

       EXPECT_EQ(myMeshCells[5].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[6].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[7].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[8].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[9].getConformingReferenceElementPolygons().size(), 4);

       EXPECT_EQ(myMeshCells[10].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[11].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[12].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[13].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[14].getConformingReferenceElementPolygons().size(), 4);

       EXPECT_EQ(myMeshCells[15].getConformingReferenceElementPolygons().size(), 3);
       EXPECT_EQ(myMeshCells[16].getConformingReferenceElementPolygons().size(), 3);
       EXPECT_EQ(myMeshCells[17].getConformingReferenceElementPolygons().size(), 3);
       EXPECT_EQ(myMeshCells[18].getConformingReferenceElementPolygons().size(), 3);
       EXPECT_EQ(myMeshCells[19].getConformingReferenceElementPolygons().size(), 2);

       double totalArea = 0;
       double domainArea = myMesh.getDomain().ComputeArea();
       for(unsigned int i = 0; i < myMeshCells.size(); i++)
           for (unsigned int j = 0; j < myMeshCells[i].getConformingReferenceElementPolygons().size(); j++)
                  totalArea += myMeshCells[i].getConformingReferenceElementPolygons()[j].ComputeArea();

       EXPECT_DOUBLE_EQ(totalArea, domainArea);
       }
       catch (const exception& ex)
       {
         FAIL();
       }

   }

   TEST(TestMeshClass, TestCreateMesh_RectangularDomain4)
   {
       //for  rectangular mesh of (4+1)x(3+1) reference elements
       //the base polygon is the convex pentagon from project 1

       vector<Point> polygonVertices;
       polygonVertices.resize(5);

       polygonVertices[0] = Point(2.5, 1.0);
       polygonVertices[1] = Point(4.0, 2.1);
       polygonVertices[2] = Point(3.4, 4.2);
       polygonVertices[3] = Point(1.6, 4.2);
       polygonVertices[4] = Point(1.0, 2.1);


       Polygon basePolygon(polygonVertices);
       Mesh myMesh(basePolygon);

       double BoundingBoxLength = myMesh.getBoundingBoxLength();
       double BoundingBoxHeight = myMesh.getBoundingBoxHeight();
       myMesh.setRectangularDomain(4*BoundingBoxLength + 1, 3*BoundingBoxHeight+1);

       try
       {
       myMesh.createMesh();
       vector<ReferenceElement> myMeshCells = myMesh.getMeshCells();

       myMesh.showMesh("showMesh4.m");

       EXPECT_EQ(myMeshCells.size(),20);
       EXPECT_EQ(myMeshCells[0].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[1].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[2].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[3].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[4].getConformingReferenceElementPolygons().size(), 3);

       EXPECT_EQ(myMeshCells[5].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[6].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[7].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[8].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[9].getConformingReferenceElementPolygons().size(), 3);

       EXPECT_EQ(myMeshCells[10].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[11].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[12].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[13].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[14].getConformingReferenceElementPolygons().size(), 3);

       EXPECT_EQ(myMeshCells[15].getConformingReferenceElementPolygons().size(), 3);
       EXPECT_EQ(myMeshCells[16].getConformingReferenceElementPolygons().size(), 3);
       EXPECT_EQ(myMeshCells[17].getConformingReferenceElementPolygons().size(), 3);
       EXPECT_EQ(myMeshCells[18].getConformingReferenceElementPolygons().size(), 3);
       EXPECT_EQ(myMeshCells[19].getConformingReferenceElementPolygons().size(), 2);

       double totalArea = 0;
       double domainArea = myMesh.getDomain().ComputeArea();
       for(unsigned int i = 0; i < myMeshCells.size(); i++)
           for (unsigned int j = 0; j < myMeshCells[i].getConformingReferenceElementPolygons().size(); j++)
                  totalArea += myMeshCells[i].getConformingReferenceElementPolygons()[j].ComputeArea();

       EXPECT_DOUBLE_EQ(totalArea, domainArea);
       }
       catch (const exception& ex)
       {
         FAIL();
       }

   }


   TEST(TestMeshClass, TestSetConvexDomain)
   {
      vector<Point> domainVertices;
      domainVertices.resize(4);
      domainVertices[0] = Point(0, 0);
      domainVertices[1] = Point(16, 0);
      domainVertices[2] = Point(20,14);
      domainVertices[3] = Point(6,16);
      Polygon domain(domainVertices);

      vector<Point> polygonVertices;
      polygonVertices.resize(4);
      polygonVertices[0] = Point(0, 2);
      polygonVertices[1] = Point(1, 0);
      polygonVertices[2] = Point(4, 3);
      polygonVertices[3] = Point(3, 4);
      Polygon basePolygon(polygonVertices);

      Mesh myMesh(basePolygon);
      myMesh.setConvexDomain(domain);

      try
      {
          EXPECT_EQ(myMesh.getDomainBoundingBoxHeight(), 16);
          EXPECT_EQ(myMesh.getDomainBoundingBoxLength(), 20);
          EXPECT_EQ(myMesh.getMaxNumRefElementsPerColumn(), 4);
          EXPECT_EQ(myMesh.getMaxNumRefElementsPerRow(), 5);
      }
      catch (const exception& ex)
      {
          FAIL();
      }


   }

   TEST(TestMeshClass, TestCreateMesh_ConvexDomain1a)
   {   //the test polygon is a quadrilateral
       //the domain is a quadrilateral

       vector<Point> domainVertices;
       domainVertices.resize(4);
       domainVertices[0] = Point(0, 0);
       domainVertices[1] = Point(16, 0);
       domainVertices[2] = Point(20,14);
       domainVertices[3] = Point(6,16);
       Polygon domain(domainVertices);

       vector<Point> polygonVertices;
       polygonVertices.resize(4);
       polygonVertices[0] = Point(0, 2);
       polygonVertices[1] = Point(1, 0);
       polygonVertices[2] = Point(4, 3);
       polygonVertices[3] = Point(3, 4);
       Polygon basePolygon(polygonVertices);

       Mesh myMesh(basePolygon);
       myMesh.setConvexDomain(domain);


       try
       {
       myMesh.createMesh();
       vector<ReferenceElement> myMeshCells = myMesh.getMeshCells();

       myMesh.showMesh("showMeshConvexDomain1a.m");

       EXPECT_EQ(myMeshCells.size(),19);
       EXPECT_EQ(myMeshCells[0].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[1].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[2].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[3].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[4].getConformingReferenceElementPolygons().size(), 3);

       EXPECT_EQ(myMeshCells[5].getConformingReferenceElementPolygons().size(), 3);
       EXPECT_EQ(myMeshCells[6].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[7].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[8].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[9].getConformingReferenceElementPolygons().size(), 4);

       EXPECT_EQ(myMeshCells[10].getConformingReferenceElementPolygons().size(), 1);
       EXPECT_EQ(myMeshCells[11].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[12].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[13].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[14].getConformingReferenceElementPolygons().size(), 5);

       EXPECT_EQ(myMeshCells[15].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[16].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[17].getConformingReferenceElementPolygons().size(), 4);
       EXPECT_EQ(myMeshCells[18].getConformingReferenceElementPolygons().size(), 4);

       double totalArea = 0;
       double domainArea = myMesh.getDomain().ComputeArea();
       for(unsigned int i = 0; i < myMeshCells.size(); i++)
           for (unsigned int j = 0; j < myMeshCells[i].getConformingReferenceElementPolygons().size(); j++)
                  totalArea += myMeshCells[i].getConformingReferenceElementPolygons()[j].ComputeArea();

       EXPECT_DOUBLE_EQ(totalArea, domainArea);

       }

       catch (const exception& ex)
       {
           FAIL();
       }


   }

   TEST(TestMeshClass, TestCreateMesh_ConvexDomain1b)
   {
       //the test polygon is the convex hexagon from project 1
       //the domain is a quadrilateral
       vector<Point> domainVertices;
       domainVertices.resize(4);
       domainVertices[0] = Point(0, 0);
       domainVertices[1] = Point(16, 0);
       domainVertices[2] = Point(20,14);
       domainVertices[3] = Point(6,16);
       Polygon domain(domainVertices);

       vector<Point> polygonVertices;
       polygonVertices.resize(6);
       polygonVertices[0] = Point(1.5, 1.0);
       polygonVertices[1] = Point(5.6, 1.5);
       polygonVertices[2] = Point(5.5, 4.8);
       polygonVertices[3] = Point(4.0, 6.2);
       polygonVertices[4] = Point(3.2, 4.2);
       polygonVertices[5] = Point(1.0, 4.0);
       Polygon basePolygon(polygonVertices);

       Mesh myMesh(basePolygon);
       myMesh.setConvexDomain(domain);

       try
       {
       myMesh.createMesh();
       vector<ReferenceElement> myMeshCells = myMesh.getMeshCells();

       myMesh.showMesh("showMeshConvexDomain1b.m");

       EXPECT_EQ(myMeshCells.size(),15);
       EXPECT_EQ(myMeshCells[0].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[1].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[2].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[3].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[4].getConformingReferenceElementPolygons().size(), 3);

       EXPECT_EQ(myMeshCells[5].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[6].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[7].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[8].getConformingReferenceElementPolygons().size(), 1);
       EXPECT_EQ(myMeshCells[9].getConformingReferenceElementPolygons().size(), 3);

       EXPECT_EQ(myMeshCells[10].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[11].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[12].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[13].getConformingReferenceElementPolygons().size(), 4);
       EXPECT_EQ(myMeshCells[14].getConformingReferenceElementPolygons().size(), 2);


       double totalArea = 0;
       double domainArea = myMesh.getDomain().ComputeArea();
       for(unsigned int i = 0; i < myMeshCells.size(); i++)
           for (unsigned int j = 0; j < myMeshCells[i].getConformingReferenceElementPolygons().size(); j++)
                  totalArea += myMeshCells[i].getConformingReferenceElementPolygons()[j].ComputeArea();

       EXPECT_DOUBLE_EQ(totalArea, domainArea);

       }

       catch (const exception& ex)
       {
           FAIL();
       }


   }

   TEST(TestMeshClass, TestCreateMesh_ConvexDomain1c)
   {
       //the domain is a quadrilateral
       //the base polygon is D'Auria's polygon with the shape of a sigma

       vector<Point> domainVertices;
       domainVertices.resize(4);
       domainVertices[0] = Point(0, 0);
       domainVertices[1] = Point(16, 0);
       domainVertices[2] = Point(20,14);
       domainVertices[3] = Point(6,16);
       Polygon domain(domainVertices);

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
       Polygon basePolygon(polygonVertices);

       Mesh myMesh(basePolygon);
       myMesh.setConvexDomain(domain);

       try
       {
       myMesh.createMesh();
       vector<ReferenceElement> myMeshCells = myMesh.getMeshCells();

       myMesh.showMesh("showMeshConvexDomain1c.m");

       EXPECT_EQ(myMeshCells.size(),14);
       EXPECT_EQ(myMeshCells[0].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[1].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[2].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[3].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[4].getConformingReferenceElementPolygons().size(), 5);

       EXPECT_EQ(myMeshCells[5].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[6].getConformingReferenceElementPolygons().size(), 3);
       EXPECT_EQ(myMeshCells[7].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[8].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[9].getConformingReferenceElementPolygons().size(), 5);

       EXPECT_EQ(myMeshCells[10].getConformingReferenceElementPolygons().size(), 4);
       EXPECT_EQ(myMeshCells[11].getConformingReferenceElementPolygons().size(), 1);
       EXPECT_EQ(myMeshCells[12].getConformingReferenceElementPolygons().size(), 3);
       EXPECT_EQ(myMeshCells[13].getConformingReferenceElementPolygons().size(), 2);


       double totalArea = 0;
       double domainArea = myMesh.getDomain().ComputeArea();
       for(unsigned int i = 0; i < myMeshCells.size(); i++)
           for (unsigned int j = 0; j < myMeshCells[i].getConformingReferenceElementPolygons().size(); j++)
                  totalArea += myMeshCells[i].getConformingReferenceElementPolygons()[j].ComputeArea();

       EXPECT_DOUBLE_EQ(totalArea, domainArea);

       }

       catch (const exception& ex)
       {
           FAIL();
       }


   }


   TEST(TestMeshClass, TestCreateMesh_ConvexDomain2a)
   {   //the test polygon is a quadrilateral
       //the domain is an hexagon


       vector<Point> domainVertices;
       domainVertices.resize(6);
       domainVertices[0] = Point(6, 0);
       domainVertices[1] = Point(14.2, 2.2);
       domainVertices[2] = Point(16.39,10.39);
       domainVertices[3] = Point(10.39, 16.39);
       domainVertices[4] = Point(2.2,14.2);
       domainVertices[5] = Point(0,6);
       Polygon domain(domainVertices);

       vector<Point> polygonVertices;
       polygonVertices.resize(4);
       polygonVertices[0] = Point(0, 2);
       polygonVertices[1] = Point(1, 0);
       polygonVertices[2] = Point(4, 3);
       polygonVertices[3] = Point(3, 4);
       Polygon basePolygon(polygonVertices);

       Mesh myMesh(basePolygon);
       myMesh.setConvexDomain(domain);


       try
       {
       myMesh.createMesh();
       vector<ReferenceElement> myMeshCells = myMesh.getMeshCells();

       myMesh.showMesh("showMeshConvexDomain2a.m");

       EXPECT_EQ(myMeshCells.size(),18);
       EXPECT_EQ(myMeshCells[0].getConformingReferenceElementPolygons().size(), 4);
       EXPECT_EQ(myMeshCells[1].getConformingReferenceElementPolygons().size(), 4);
       EXPECT_EQ(myMeshCells[2].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[3].getConformingReferenceElementPolygons().size(), 3);
       EXPECT_EQ(myMeshCells[4].getConformingReferenceElementPolygons().size(), 4);

       EXPECT_EQ(myMeshCells[5].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[6].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[7].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[8].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[9].getConformingReferenceElementPolygons().size(), 5);

       EXPECT_EQ(myMeshCells[10].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[11].getConformingReferenceElementPolygons().size(), 4);
       EXPECT_EQ(myMeshCells[12].getConformingReferenceElementPolygons().size(), 3);
       EXPECT_EQ(myMeshCells[13].getConformingReferenceElementPolygons().size(), 2);
       EXPECT_EQ(myMeshCells[14].getConformingReferenceElementPolygons().size(), 5);

       EXPECT_EQ(myMeshCells[15].getConformingReferenceElementPolygons().size(), 4);
       EXPECT_EQ(myMeshCells[16].getConformingReferenceElementPolygons().size(), 4);
       EXPECT_EQ(myMeshCells[17].getConformingReferenceElementPolygons().size(), 3);


       double totalArea = 0;
       double domainArea = myMesh.getDomain().ComputeArea();
       for(unsigned int i = 0; i < myMeshCells.size(); i++)
           for (unsigned int j = 0; j < myMeshCells[i].getConformingReferenceElementPolygons().size(); j++)
                  totalArea += myMeshCells[i].getConformingReferenceElementPolygons()[j].ComputeArea();

       EXPECT_DOUBLE_EQ(totalArea, domainArea);

       }

       catch (const exception& ex)
       {
           FAIL();
       }


   }

   TEST(TestMeshClass, TestCreateMesh_ConvexDomain2b)
   {   //the test polygon is the convex hexagon from project 1
       //the domain is an hexagon


       vector<Point> domainVertices;
       domainVertices.resize(6);
       domainVertices[0] = Point(6, 0);
       domainVertices[1] = Point(14.2, 2.2);
       domainVertices[2] = Point(16.39,10.39);
       domainVertices[3] = Point(10.39, 16.39);
       domainVertices[4] = Point(2.2,14.2);
       domainVertices[5] = Point(0,6);
       Polygon domain(domainVertices);

       vector<Point> polygonVertices;
       polygonVertices.resize(6);
       polygonVertices[0] = Point(1.5, 1.0);
       polygonVertices[1] = Point(5.6, 1.5);
       polygonVertices[2] = Point(5.5, 4.8);
       polygonVertices[3] = Point(4.0, 6.2);
       polygonVertices[4] = Point(3.2, 4.2);
       polygonVertices[5] = Point(1.0, 4.0);
       Polygon basePolygon(polygonVertices);

       Mesh myMesh(basePolygon);
       myMesh.setConvexDomain(domain);


       try
       {
       myMesh.createMesh();
       vector<ReferenceElement> myMeshCells = myMesh.getMeshCells();

       myMesh.showMesh("showMeshConvexDomain2b.m");

       EXPECT_EQ(myMeshCells.size(),14);
       EXPECT_EQ(myMeshCells[0].getConformingReferenceElementPolygons().size(), 3);
       EXPECT_EQ(myMeshCells[1].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[2].getConformingReferenceElementPolygons().size(), 4);
       EXPECT_EQ(myMeshCells[3].getConformingReferenceElementPolygons().size(), 3);
       EXPECT_EQ(myMeshCells[4].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[5].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[6].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[7].getConformingReferenceElementPolygons().size(), 4);
       EXPECT_EQ(myMeshCells[8].getConformingReferenceElementPolygons().size(), 4);
       EXPECT_EQ(myMeshCells[9].getConformingReferenceElementPolygons().size(), 5);

       EXPECT_EQ(myMeshCells[10].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[11].getConformingReferenceElementPolygons().size(), 3);
       EXPECT_EQ(myMeshCells[12].getConformingReferenceElementPolygons().size(), 1);
       EXPECT_EQ(myMeshCells[13].getConformingReferenceElementPolygons().size(), 3);

       double totalArea = 0;
       double domainArea = myMesh.getDomain().ComputeArea();
       for(unsigned int i = 0; i < myMeshCells.size(); i++)
           for (unsigned int j = 0; j < myMeshCells[i].getConformingReferenceElementPolygons().size(); j++)
                  totalArea += myMeshCells[i].getConformingReferenceElementPolygons()[j].ComputeArea();

       EXPECT_DOUBLE_EQ(totalArea, domainArea);

       }

       catch (const exception& ex)
       {
           FAIL();
       }


   }

   TEST(TestMeshClass, TestCreateMesh_ConvexDomain2c)
   {   //the base polygon is D'Auria's polygon with the shape of a sigma
       //the domain is an hexagon


       vector<Point> domainVertices;
       domainVertices.resize(6);
       domainVertices[0] = Point(6, 0);
       domainVertices[1] = Point(14.2, 2.2);
       domainVertices[2] = Point(16.39,10.39);
       domainVertices[3] = Point(10.39, 16.39);
       domainVertices[4] = Point(2.2,14.2);
       domainVertices[5] = Point(0,6);
       Polygon domain(domainVertices);

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
       Polygon basePolygon(polygonVertices);

       Mesh myMesh(basePolygon);
       myMesh.setConvexDomain(domain);


       try
       {
       myMesh.createMesh();
       vector<ReferenceElement> myMeshCells = myMesh.getMeshCells();

       myMesh.showMesh("showMeshConvexDomain2c.m");

       EXPECT_EQ(myMeshCells.size(),11);
       EXPECT_EQ(myMeshCells[0].getConformingReferenceElementPolygons().size(), 4);
       EXPECT_EQ(myMeshCells[1].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[2].getConformingReferenceElementPolygons().size(), 3);
       EXPECT_EQ(myMeshCells[3].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[4].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[5].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[6].getConformingReferenceElementPolygons().size(), 4);
       EXPECT_EQ(myMeshCells[7].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[8].getConformingReferenceElementPolygons().size(), 5);
       EXPECT_EQ(myMeshCells[9].getConformingReferenceElementPolygons().size(), 1);
       EXPECT_EQ(myMeshCells[10].getConformingReferenceElementPolygons().size(),3);


       double totalArea = 0;
       double domainArea = myMesh.getDomain().ComputeArea();
       for(unsigned int i = 0; i < myMeshCells.size(); i++)
           for (unsigned int j = 0; j < myMeshCells[i].getConformingReferenceElementPolygons().size(); j++)
                  totalArea += myMeshCells[i].getConformingReferenceElementPolygons()[j].ComputeArea();

       EXPECT_DOUBLE_EQ(totalArea, domainArea);

       }

       catch (const exception& ex)
       {
           FAIL();
       }
   }

}

#endif
