#ifndef __TEST_SEGMENTCLASS_H
#define __TEST_SEGMENTCLASS_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>

#include "Segment.hpp"

using namespace testing;
using namespace std;

namespace SegmentTesting {

    TEST(TestSegmentClass, SetterGetterMethods)
    {
        Point start{1, 2};
        Point end{2, 3};
        Segment segment;

        segment.setStart(start);
        segment.setEnd(end);

        try
        {
            EXPECT_EQ(segment.getStart(), start);
        }
        catch (const exception& exception)
        {
            FAIL();
        }

        try
        {
            EXPECT_EQ(segment.getEnd(), end);
        }
        catch (const exception& exception)
        {
            FAIL();
        }

        try
        {
            segment.setSegment(start, end);
            EXPECT_EQ(segment.getStart(), start);
            EXPECT_EQ(segment.getEnd(), end);
        }
        catch (const exception& exception)
        {
            FAIL();
        }
    }

    TEST(TestSegmentClass, TangentMethods)
    {
        Point start{1, 2};
        Point end{2, 3};
        Segment segment(start, end);

        const Vector2d tangentVector(1, 1);
        try
        {
            EXPECT_EQ(segment.getTangent() , tangentVector);
        }
        catch (const exception& exception)
        {
            FAIL();
        }

        try
        {
            EXPECT_EQ(segment.computeTangent() , tangentVector);
        }
        catch (const exception& exception)
        {
            FAIL();
        }
    }

    TEST(TestSegmentClass, PointOnTheRightSide)
    {
        Point start{1, 0};
        Point end{2, 0};
        Segment segment;

        Point test1(0.0,-3.0);
        Point test2(1.5,0.0);
        Point test3(0.0,13.0);

        segment = Segment(start, end);
        segment.computeTangent();

        try
        {
            EXPECT_EQ(1, segment.pointOnTheRightSide(test1));
            EXPECT_EQ(0, segment.pointOnTheRightSide(test2));
            EXPECT_EQ(-1, segment.pointOnTheRightSide(test3));
        }
        catch (const exception& exception)
        {
            FAIL();
        }

    }
}

#endif
