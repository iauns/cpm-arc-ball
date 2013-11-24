/// \author James Hughes
/// \date   November 2013

#ifndef TESTENVIRONMENT_HPP
#define TESTENVIRONMENT_HPP

#include <memory>

#include <gl-batch-env/BatchEnvironment.hpp>
#include <gtest/gtest.h>

class GlobalTestEnvironment : public ::testing::Environment
{
public:

  GlobalTestEnvironment()
  {
    if (mInstance != nullptr)
      throw std::runtime_error("Global test environment has already been constructed!");

    mInstance = this;
    mEnvironment = std::shared_ptr<CPM_GL_BATCH_ENV_NS::BatchEnvironment>(
        new CPM_GL_BATCH_ENV_NS::BatchEnvironment(640, 480, 32, 24, 0, true, false));
  }
  
  static GlobalTestEnvironment* instance()
  {
    if (mInstance == nullptr)
      throw std::runtime_error("Global test environment not initialized!");
    return mInstance;
  }

  std::shared_ptr<CPM_GL_BATCH_ENV_NS::BatchEnvironment>getBatchEnvironment() const {return mEnvironment;}

protected:

  std::shared_ptr<CPM_GL_BATCH_ENV_NS::BatchEnvironment> mEnvironment;

  static GlobalTestEnvironment* mInstance;
};

#endif 

