file(GLOB SRC_CORE_GLOB ./core/*.hpp ./core/*.cpp)

add_executable(${PROJECT_NAME} main.cpp ${SRC_CORE_GLOB})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
