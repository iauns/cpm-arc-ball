
#include <cstdlib>
#include <iostream>
#include "gtest/gtest.h"

#include "gl-batch-context/Context.hpp"

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

