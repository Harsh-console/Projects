cmake_minimum_required(VERSION 3.10)
project(SpinningDonut)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/include/glm)

add_executable(SpinningDonut main.cpp glad.c)

link_directories(${CMAKE_SOURCE_DIR}/glfw/lib-mingw-w64)
target_link_libraries(SpinningDonut glfw3 opengl32 gdi32)
