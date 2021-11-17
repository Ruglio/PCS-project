#include "test_segment.hpp"
#include "test_polygon.hpp"
#include "test_intersector1D1D.hpp"
#include "test_intersectorpolygonline.hpp"
#include "test_polygoncutter.hpp"
#include "test_referenceelement.hpp"
#include "test_mesh.hpp"
#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}


