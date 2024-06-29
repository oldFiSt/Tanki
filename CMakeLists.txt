cmake_minimum_required(VERSION 3.0.0)
set(PROJECT_NAME glab)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw) 

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)