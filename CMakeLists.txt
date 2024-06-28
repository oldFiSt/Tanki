cmake_minimum_required(VERSION 3.5)
project(glab)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/external/glm
    ${PROJECT_SOURCE_DIR}/external/glfw/include
)

add_subdirectory(external/glfw)

find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

add_executable(glab main.cpp Game.cpp)
target_link_libraries(glab GLFW::GLFW)
