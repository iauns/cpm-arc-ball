
/// \author James Hughes
/// \date   November 2013

#ifndef IAUNS_SPIREFIXTURE_HPP
#define IAUNS_SPIREFIXTURE_HPP

#include <gl-batch-env/BatchEnvironment.hpp>
#include <spire/Interface.h>
#include <gtest/gtest.h>

#include "GlobalTestEnvironment.hpp"

class SpireContext : public CPM_SPIRE_NS::Context
{
public:
  SpireContext(std::shared_ptr<CPM_GL_BATCH_ENV_NS::BatchEnvironment> env);

  void makeCurrent() override;
  void swapBuffers() override;

private:
  std::shared_ptr<CPM_GL_BATCH_ENV_NS::BatchEnvironment> mEnv;
};

class SpireTestFixture : public testing::Test
{
public:
  SpireTestFixture() {}

  virtual void SetUp() override;
  virtual void TearDown() override;

  void addDefaultAttributes();

  std::shared_ptr<CPM_SPIRE_NS::Interface>    mSpire;

private:

  std::shared_ptr<SpireContext>         mSpireContext;
};

#endif 
