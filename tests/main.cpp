
#include <cstdlib>
#include <iostream>

#include "gl-batch-context/Context.hpp"

int main(int /*argc*/, char** /*argv*/)
{
  CPM_GL_CONTEXT_NS::Context* glContext = 
      CPM_GL_CONTEXT_NS::Context::createBatchContext(
          640, 480, 32, 32, 0, false, false);

  // Add a few quick OpenGL calls here to verify the context is working.

  // Now that we are finished, delete the context.
  delete glContext;
}

