cmake_minimum_required (VERSION 2.8.11)
project(voxel-renderer CXX)

# check for dependencies
include(cmake/FindSDL2.cmake)
if (NOT SDL2_FOUND)
    message(FATAL_ERROR "SDL2 not found.")
endif()

include(cmake/FindSDL2_image.cmake)
if (NOT SDL2_IMAGE_FOUND)
    message(FATAL_ERROR "SDL2_image not found.")
endif()

include(FindOpenGL)
if (NOT OPENGL_FOUND)
    message(FATAL_ERROR "OpenGL not found.")
endif()

include(FindGLEW)
if (NOT GLEW_FOUND)
    message(FATAL_ERROR "GLEW not found.")
endif()

include(cmake/FindGLM.cmake)
if (NOT GLM_FOUND)
    message(FATAL_ERROR "GLM not found.")
endif()

# include dependencies into project
#include_directories(${SDL2_INCLUDE_DIR})
#include_directories(${SDL2_IMAGE_INCLUDE_DIR})
#include_directories(${OPENGL_INCLUDE_DIR})
#include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})

# copy assets directory
file(COPY ./assets DESTINATION .)

# proceed to source files
add_subdirectory(./src)
