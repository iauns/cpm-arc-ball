
/// \author James Hughes
/// \date   November 2013

#ifndef IAUNS_SPIREFIXTURE_HPP
#define IAUNS_SPIREFIXTURE_HPP

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
  InterfaceTestFixture () {}

  virtual void SetUp() override
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

  virtual void TearDown() override
  {
    mSpire.reset();
  }

  void addDefaultAttributes()
  {
    mSpire->addShaderAttribute("aPos",         3,  false,  sizeof(float) * 3,  spire::Interface::TYPE_FLOAT);
    mSpire->addShaderAttribute("aNormal",      3,  false,  sizeof(float) * 3,  spire::Interface::TYPE_FLOAT);
    mSpire->addShaderAttribute("aColorFloat",  4,  false,  sizeof(float) * 4,  spire::Interface::TYPE_FLOAT);
    mSpire->addShaderAttribute("aColor",       4,  true,   sizeof(char) * 4,   spire::Interface::TYPE_UBYTE);

    // Used to test attribute mis-alignment.
    mSpire->addShaderAttribute("aFieldData",   1,  false,  sizeof(float) * 1,  spire::Interface::TYPE_FLOAT);
  }

  std::shared_ptr<spire::Interface>     mSpire;
  std::unique_ptr<TestCamera>           mCamera;
};

#endif 
