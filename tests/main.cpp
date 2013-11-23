
#include <cstdlib>
#include <iostream>
#include "gtest/gtest.h"

#include "gl-batch-context/Context.hpp"

/// \todo Use lodepng to write png files. It's small and we can easily
///       create a CPM external for it.
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

