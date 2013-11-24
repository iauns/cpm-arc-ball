/// \author James Hughes
/// \date   November 2013

#ifndef TESTENVIRONMENT_HPP
#define TESTENVIRONMENT_HPP

#include <memory>

#include <gtest/gtest.h>

namespace CPM_GL_BATCH_ENV_NS
{
  class BatchEnvironment;
}

class GlobalTestEnvironment : public ::testing::Environment
{
public:
  GlobalTestEnvironment();
  static GlobalTestEnvironment* instance();
  std::shared_ptr<CPM_GL_BATCH_ENV_NS::BatchEnvironment> getBatchEnvironment() const {return mEnvironment;}

protected:
  std::shared_ptr<CPM_GL_BATCH_ENV_NS::BatchEnvironment> mEnvironment;
  static GlobalTestEnvironment* mInstance;
};

#endif 

