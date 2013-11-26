
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
  std::shared_ptr<CPM_GL_BATCH_ENV_NS::BatchEnvironment> ctx 
      = GlobalTestEnvironment::instance()->getBatchEnvironment();

  mSpireContext = std::shared_ptr<SpireContext>(new SpireContext(ctx));

  ctx->makeCurrent();
  mSpire = std::shared_ptr<CPM_SPIRE_NS::Interface>(
      new CPM_SPIRE_NS::Interface(mSpireContext, shaderSearchDirs));

  // Add default attributes.
  addDefaultAttributes();

  // Begin a new frame.
  beginFrame();
}

//------------------------------------------------------------------------------
void SpireTestFixture::TearDown()
{
  mSpire.reset();
  mSpireContext.reset();
}

//------------------------------------------------------------------------------
void SpireTestFixture::addDefaultAttributes()
{
  mSpire->addShaderAttribute("aPos",         3,  false,  sizeof(float) * 3,  CPM_SPIRE_NS::Interface::TYPE_FLOAT);
  mSpire->addShaderAttribute("aNormal",      3,  false,  sizeof(float) * 3,  CPM_SPIRE_NS::Interface::TYPE_FLOAT);
  mSpire->addShaderAttribute("aColorFloat",  4,  false,  sizeof(float) * 4,  CPM_SPIRE_NS::Interface::TYPE_FLOAT);
  mSpire->addShaderAttribute("aColor",       4,  true,   sizeof(char) * 4,   CPM_SPIRE_NS::Interface::TYPE_UBYTE);

  // Used to test attribute mis-alignment.
  mSpire->addShaderAttribute("aFieldData",   1,  false,  sizeof(float) * 1,  CPM_SPIRE_NS::Interface::TYPE_FLOAT);
}

//------------------------------------------------------------------------------
void SpireTestFixture::beginFrame()
{
  // Do not even attempt to render if the framebuffer is not complete.
  // This can happen when the rendering window is hidden (in SCIRun5 for
  // example);
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
  {
    std::cerr << "Incomplete framebuffer!" << std::endl;
    return;
  }

  /// \todo Move this outside of the interface!
  GL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
  GL(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT));

  CPM_SPIRE_NS::GPUState defaultGPUState;
  mSpire->applyGPUState(defaultGPUState, true); // true = force application of state.
}


