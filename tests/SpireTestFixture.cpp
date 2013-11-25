/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2013 Scientific Computing and Imaging Institute,
   University of Utah.


   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
*/

/// \author James Hughes
/// \date   November 2013

#include "SpireTestFixture.hpp"


//------------------------------------------------------------------------------
SpireContext::SpireContext(std::shared_ptr<CPM_GL_BATCH_ENV_NS::BatchEnvironment> env) :
    mEnv(env)
{ }

//------------------------------------------------------------------------------
void SpireContext::makeCurrent()
{
  mEnv->makeCurrent();
}

//------------------------------------------------------------------------------
void SpireContext::swapBuffers()
{
  mEnv->swapBuffers();
}



//------------------------------------------------------------------------------
// SpireTestFixture implementation
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
void SpireTestFixture::SetUp()
{
  std::vector<std::string> shaderSearchDirs;
  shaderSearchDirs.push_back("shaders");

  // Build spire using the context from GlobalTestEnvironment.
  std::shared_ptr<spire::Context> ctx = GlobalTestEnvironment::instance()->getContext();
  ctx->makeCurrent();
  mSpire = std::shared_ptr<spire::Interface>(new spire::Interface(
          ctx, shaderSearchDirs));

  // Add default attributes.
  addDefaultAttributes();

  // Build camera that we will use for testing purposes.
  mCamera = std::unique_ptr<TestCamera>(new TestCamera);
}

//------------------------------------------------------------------------------
void SpireTestFixture::TearDown()
{
  mSpire.reset();
}

//------------------------------------------------------------------------------
void SpireTestFixture::addDefaultAttributes()
{
  mSpire->addShaderAttribute("aPos",         3,  false,  sizeof(float) * 3,  spire::Interface::TYPE_FLOAT);
  mSpire->addShaderAttribute("aNormal",      3,  false,  sizeof(float) * 3,  spire::Interface::TYPE_FLOAT);
  mSpire->addShaderAttribute("aColorFloat",  4,  false,  sizeof(float) * 4,  spire::Interface::TYPE_FLOAT);
  mSpire->addShaderAttribute("aColor",       4,  true,   sizeof(char) * 4,   spire::Interface::TYPE_UBYTE);

  // Used to test attribute mis-alignment.
  mSpire->addShaderAttribute("aFieldData",   1,  false,  sizeof(float) * 1,  spire::Interface::TYPE_FLOAT);
}


