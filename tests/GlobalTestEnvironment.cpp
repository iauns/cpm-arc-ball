/// \author James Hughes
/// \date   November 2013

#include "GlobalTestEnvironment.hpp"
#include <gl-batch-env/BatchEnvironment.hpp>

GlobalTestEnvironment* GlobalTestEnvironment::mInstance = nullptr;

GlobalTestEnvironment::GlobalTestEnvironment()
{
  if (mInstance != nullptr)
    throw std::runtime_error("Global test environment has already been constructed!");

  mInstance = this;
  mEnvironment = std::shared_ptr<CPM_GL_BATCH_ENV_NS::BatchEnvironment>(
      new CPM_GL_BATCH_ENV_NS::BatchEnvironment(600, 600, 32, 24, 8, true, false));
}

GlobalTestEnvironment* GlobalTestEnvironment::instance()
{
  if (mInstance == nullptr)
    throw std::runtime_error("Global test environment not initialized!");
  return mInstance;
}

