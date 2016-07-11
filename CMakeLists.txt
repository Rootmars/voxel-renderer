cmake_minimum_required (VERSION 2.8.11)
project(voxel-renderer CXX)

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

include_directories(include)
include_directories(include/core)

file(GLOB SRC_CORE src/core/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_CORE})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
