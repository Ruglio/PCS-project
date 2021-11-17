#ifndef __TEST_INTERSECTOR1D1D_H
#define __TEST_INTERSECTOR1D1D_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>

#include "Intersector1D1D.hpp"

using namespace testing;

namespace Intersector1D1DTesting {

TEST(TestIntersector1D1D, TestParallelIntersection)
{
  Vector2d a(0, 0);
  Vector2d b(4, 0);
  Vector2d c(1, 0);
  Vector2d d(2, 0);

  Intersector1D1D intersectorNew;

  intersectorNew.SetFirstSegment(a, b);
  intersectorNew.SetSecondSegment(c, d);
  EXPECT_TRUE(intersectorNew.ComputeIntersection());
  EXPECT_EQ(intersectorNew.TypeIntersection(), IIntersector1D1D::IntersectionParallelOnSegment);
  EXPECT_FLOAT_EQ(0.25, intersectorNew.FirstParametricCoordinate());
  EXPECT_FLOAT_EQ(0.5, intersectorNew.SecondParametricCoordinate());
}

TEST(TestIntersector1D1D, TestSegmentIntersection)
{
  Vector2d a(1, 0);
  Vector2d b(5, 0);
  Vector2d c(3, -6);
  Vector2d d(3, 6);

  Intersector1D1D intersector;

  intersector.SetFirstSegment(a, b);
  intersector.SetSecondSegment(c, d);
  EXPECT_TRUE(intersector.ComputeIntersection());
  EXPECT_EQ(intersector.TypeIntersection(), IIntersector1D1D::IntersectionOnSegment);
  EXPECT_FLOAT_EQ(0.5, intersector.SecondParametricCoordinate());
  EXPECT_FLOAT_EQ(0.5, intersector.FirstParametricCoordinate());
  EXPECT_LE(intersector.FirstParametricCoordinate(), 1.0);
  EXPECT_GE(intersector.FirstParametricCoordinate(), 0.0);
}

TEST(TestIntersector1D1D, TestOnLineIntersection)
{
  Vector2d a(3, 6);
  Vector2d b(3, 2);
  Vector2d c(5, 0);
  Vector2d d(1, 0);

  Intersector1D1D intersector;

  intersector.SetFirstSegment(a, b);
  intersector.SetSecondSegment(c, d);
  EXPECT_TRUE(intersector.ComputeIntersection());
  EXPECT_EQ(intersector.TypeIntersection(), IIntersector1D1D::IntersectionOnLine);
  EXPECT_FLOAT_EQ(1.5, intersector.FirstParametricCoordinate());
  EXPECT_FLOAT_EQ(0.5, intersector.SecondParametricCoordinate());
  EXPECT_GE(intersector.FirstParametricCoordinate(), 1.0);
}
}
#endif // __TEST_INTERSECTOR1D1D_H
