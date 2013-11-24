
#include <cstdlib>
#include <iostream>
#include <exception>
#include <memory>

#include <gtest/gtest.h>
#include <spire/Interface.h>

#include "GlobalTestEnvironment.hpp"

int main(int argc, char** argv)
{
  // Add a global test environment that initializes an OpenGL batch renderer.
  ::testing::AddGlobalTestEnvironment(new GlobalTestEnvironment());

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

