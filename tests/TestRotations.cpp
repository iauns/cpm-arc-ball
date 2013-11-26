/// \author James Hughes
/// \date   November 2013

#include "GlobalTestEnvironment.hpp"
#include "SpireTestFixture.hpp"
#include <spire/src/FileUtil.h>

void compareFBOWithExistingFile(const std::string& filename)
{
  // Print out the frame and compare it.
#ifdef TEST_OUTPUT_IMAGES
  {
    std::string imageName = filename;

    std::string targetImage = TEST_IMAGE_OUTPUT_DIR;
    targetImage += "/" + imageName;
    GlobalTestEnvironment::instance()->getBatchEnvironment()->writeFBO(targetImage);

    EXPECT_TRUE(CPM_SPIRE_NS::fileExists(targetImage)) << "Failed to write output image! " << targetImage;

#ifdef TEST_PERCEPTUAL_COMPARE
    // Perform the perceptual comparison using the given regression directory.
    std::string compImage = TEST_IMAGE_COMPARE_DIR;
    compImage += "/" + imageName;

    ASSERT_TRUE(CPM_SPIRE_NS::fileExists(compImage)) << "Failed to find comparison image! " << compImage;
    // Test using perceptula comparison program that the user has provided
    // (hopefully).
    std::string command = TEST_PERCEPTUAL_COMPARE_BINARY;
    command += " -threshold 50 ";
    command += targetImage + " " + compImage;

    // Usually the return code of std::system is implementation specific. But the
    // majority of systems end up returning the exit code of the program.
    if (std::system(command.c_str()) != 0)
    {
      // The images are NOT the same. Alert the user.
      FAIL() << "Perceptual compare of " << imageName << " failed.";
    }
#endif
  }
#endif
}

TEST_F(SpireTestFixture, TestRenderingWithSR5Object)
{
  // Test various functions in Object and ObjectPass.
  std::vector<float> vboData = 
  {
    -1.0f,  1.0f,  0.0f,
     1.0f,  1.0f,  0.0f,
    -1.0f, -1.0f,  0.0f,
     1.0f, -1.0f,  0.0f
  };
  std::vector<std::string> attribNames = {"aPos"};

  std::vector<uint16_t> iboData =
  {
    0, 1, 2, 3
  };
  CPM_SPIRE_NS::Interface::IBO_TYPE iboType = CPM_SPIRE_NS::Interface::IBO_16BIT;

  // This is pretty contorted interface due to the marshalling between
  // std::vector<float> and std::vector<uint8_t>. In practice, you would want
  // to calculate the size of your VBO and using one std::vector<uint8_t> and
  // reserve the necessary space in it. Then cast it's contents to floats or
  // uint16_t as necessary (attributes can have a wide array of types, including
  // half floats).
  uint8_t*  rawBegin;
  size_t    rawSize;

  // Copy vboData into vector of uint8_t. Using std::copy.
  std::shared_ptr<std::vector<uint8_t>> rawVBO(new std::vector<uint8_t>());
  rawSize = vboData.size() * (sizeof(float) / sizeof(uint8_t));
  rawVBO->reserve(rawSize);
  rawBegin = reinterpret_cast<uint8_t*>(&vboData[0]);
  rawVBO->assign(rawBegin, rawBegin + rawSize);

  // Copy iboData into vector of uint8_t. Using std::vector::assign.
  std::shared_ptr<std::vector<uint8_t>> rawIBO(new std::vector<uint8_t>());
  rawSize = iboData.size() * (sizeof(uint16_t) / sizeof(uint8_t));
  rawIBO->reserve(rawSize);
  rawBegin = reinterpret_cast<uint8_t*>(&iboData[0]);
  rawIBO->assign(rawBegin, rawBegin + rawSize);

  // Add necessary VBO's and IBO's
  std::string vbo1 = "vbo1";
  std::string ibo1 = "ibo1";
  mSpire->addVBO(vbo1, rawVBO, attribNames);
  mSpire->addIBO(ibo1, rawIBO, iboType);

  std::string obj1 = "obj1";
  mSpire->addObject(obj1);
  
  std::string shader1 = "UniformColor";
  mSpire->addPersistentShader(
      shader1, 
      { std::make_tuple("UniformColor.vsh", CPM_SPIRE_NS::Interface::VERTEX_SHADER), 
        std::make_tuple("UniformColor.fsh", CPM_SPIRE_NS::Interface::FRAGMENT_SHADER),
      });
  mSpire->addPassToObject(obj1, shader1, vbo1, ibo1, CPM_SPIRE_NS::Interface::TRIANGLE_STRIP);

  float aspect = static_cast<float>(640) / static_cast<float>(480);
  glm::mat4 projection = glm::perspective(0.59f, aspect, 1.0f, 2000.0f);

  glm::mat4 cam;
  cam[3] = glm::vec4(0.0f, 0.0f, 5.0f, 1.0f);

  glm::mat4 ivp = projection * glm::affineInverse(cam);

  mSpire->addObjectGlobalUniform(obj1, "uProjIVObject", ivp);

  mSpire->removeIBO(ibo1);
  mSpire->removeVBO(vbo1);

  mSpire->addObjectPassUniform(obj1, "uColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

  // Clear the frame and compare the object.
  beginFrame();
  mSpire->renderObject(obj1);

  // Compare FBO with existing file.
  //compareFBOWithExistingFile("noRotation.png");
}

