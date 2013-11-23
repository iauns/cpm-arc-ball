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

# ++ MODULE: Arc Ball
CPM_AddModule("arc_ball"
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")

# ++ MODULE: OpenGL Context Creator
CPM_AddModule("gl_context"
  GIT_REPOSITORY "https://github.com/iauns/cpm-gl-batch-context"
  GIT_TAG "origin/master")

# ++ MODULE: Spire
CPM_AddModule("spire"
  GIT_REPOSITORY "https://github.com/SCIInstitute/spire"
  GIT_TAG "origin/dev")

# ++ MODULE: Spire testing
CPM_AddModule("spire_testing"
  GIT_REPOSITORY "https://github.com/iauns/cpm-spire-testing"
  GIT_TAG "origin/master")

# ++ EXTERNAL-MODULE: Google Test
CPM_AddModule("google_test"
  GIT_REPOSITORY "https://github.com/iauns/cpm-google-test"
  GIT_TAG "origin/master")

CPM_Finish()

#-----------------------------------------------------------------------
# Copy appropriate shaders and assets
#-----------------------------------------------------------------------
CPM_GetSourceDir("spire_testing" SPIRE_TESTING_SOURCE_DIR)

# Copy shaders.
file(COPY ${SPIRE_TESTING_SOURCE_DIR}/shaders/
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/
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

add_executable(gl_test_batch ${Sources})

target_link_libraries(gl_test_batch 
  ${CPM_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${PTHREADS})

