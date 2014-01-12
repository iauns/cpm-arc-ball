if(APPLE)
  cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)
else()
  cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)
endif()

project(ArcBallTest)

#-----------------------------------------------------------------------
# C++11
#-----------------------------------------------------------------------
if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
  endif ()
endif ()

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

# ++ MODULE: Arc Ball
CPM_AddModule("arc_ball"
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")

# ++ EXTERNAL-MODULE: Google Test
CPM_AddModule("google_test"
  GIT_REPOSITORY "https://github.com/iauns/cpm-google-test"
  GIT_TAG "1.0.1"
  USE_EXISTING_VER TRUE)

# ++ MODULE: batch_testing
CPM_AddModule("batch_testing"
  GIT_REPOSITORY "https://github.com/iauns/cpm-gl-batch-testing"
  GIT_TAG "1.1.1")

CPM_Finish()

#-----------------------------------------------------------------------
# Copy appropriate shaders and assets
#-----------------------------------------------------------------------
CPM_GetSourceDir(SPIRE_TESTING_SOURCE_DIR "batch_testing")

# Copy shaders.
file(COPY ${SPIRE_TESTING_SOURCE_DIR}/shaders/
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shaders
     FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
     DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                           GROUP_READ
                           WORLD_READ WORLD_EXECUTE)

# Exported meshes.
file(COPY ${SPIRE_TESTING_SOURCE_DIR}/assets/
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets
     FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
     DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                           GROUP_READ
                           WORLD_READ WORLD_EXECUTE)

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
# Regression directory setup
#-----------------------------------------------------------------------

set(REGRESSION_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/regression")
CPM_EnsureRepoIsCurrent(
  TARGET_DIR ${REGRESSION_DATA_DIR}
  GIT_REPOSITORY "https://github.com/iauns-tests/cpm-arc-ball"
  GIT_TAG "origin/master"
  )

add_definitions(-DTEST_OUTPUT_IMAGES)
add_definitions(-DTEST_IMAGE_OUTPUT_DIR="${REGRESSION_DATA_DIR}/output")
add_definitions(-DTEST_IMAGE_COMPARE_DIR="${REGRESSION_DATA_DIR}/verified")
add_definitions(-DTEST_PERCEPTUAL_COMPARE)
add_definitions(-DTEST_PERCEPTUAL_COMPARE_BINARY="perceptualdiff")

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

# For google test...
if (UNIX)
  if (NOT APPLE)
    set(PTHREADS "-pthread")
  endif()
endif()

# Make sure we don't link against OpenGL libraries if using OSMesa
if (USE_OS_MESA)
  set(OPENGL_LIBRARIES)
endif()

add_executable(arc_ball_test ${Sources})
target_link_libraries(arc_ball_test 
  ${CPM_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${PTHREADS})

