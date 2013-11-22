if(APPLE)
  cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)
else()
  cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)
endif()

project(ArcBallTest)

#------------------------------------------------------------------------------
# Required CPM Setup - See: http://github.com/iauns/cpm
#------------------------------------------------------------------------------
set(CPM_DIR "${CMAKE_CURRENT_BINARY_DIR}/cpm-packages" CACHE TYPE STRING)
find_package(Git)
if(NOT GIT_FOUND)
  message(FATAL_ERROR "CPM requires Git.")
endif()
if (NOT EXISTS ${CPM_DIR}/CPM.cmake)
  message(STATUS "Cloning repo (https://github.com/iauns/cpm)")
  execute_process(
    COMMAND "${GIT_EXECUTABLE}" clone https://github.com/iauns/cpm ${CPM_DIR}
    RESULT_VARIABLE error_code
    OUTPUT_QUIET ERROR_QUIET)
  if(error_code)
    message(FATAL_ERROR "CPM failed to get the hash for HEAD")
  endif()
endif()
include(${CPM_DIR}/CPM.cmake)

# ++ MODULE: OpenGL Context Creator
CPM_AddModule("gl_context"
  GIT_REPOSITORY "https://github.com/iauns/cpm-gl-batch-context"
  GIT_TAG "origin/master")

# ++ MODULE: Spire
CPM_AddModule("spire"
  GIT_REPOSITORY "https://github.com/SCIInstitute/spire"
  GIT_TAG "origin/master")

# ++ MODULE: Spire testing
CPM_AddModule("spire_testing",
  GIT_REPOSITORY "https://github.com/iauns/cpm-spire-testing",
  GIT_TAG "origin/master")

# ++ MODULE: Google Test
CPM_AddModule("google_test",
  GIT_REPOSITORY "https://github.com/iauns/cpm-google-test",
  GIT_TAG "origin/master")

CPM_Finish()

#-----------------------------------------------------------------------
# Configure OpenGL
#-----------------------------------------------------------------------
find_package(OpenGL REQUIRED)

#-----------------------------------------------------------------------
# Setup strict warnings and werror
#-----------------------------------------------------------------------

if(APPLE)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wconversion -Wshadow")
endif()

#-----------------------------------------------------------------------
# Setup source
#-----------------------------------------------------------------------
# Setup spire test sources. Even though this is a batch renderer, this is
# a good test of concept.

file(GLOB Sources
  "*.cpp"
  "*.hpp"
  )

########################################################################
# Setup executable

add_executable(gl_test_batch ${Sources})

target_link_libraries(gl_test_batch 
  ${CPM_LIBRARIES}
  ${OPENGL_LIBRARIES})

