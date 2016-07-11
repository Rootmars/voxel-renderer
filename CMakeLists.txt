cmake_minimum_required (VERSION 2.8.11)
project(voxel-renderer CXX)

include(cmake/FindSDL2.cmake)
include(cmake/FindSDL2_image.cmake)
include(cmake/FindOpenGL.cmake)
include(cmake/FindGLEW.cmake)
include(cmake/FindGLM.cmake)

include_directories(include)
include_directories(include/core)

file(GLOB SRC_CORE src/core/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_CORE})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
