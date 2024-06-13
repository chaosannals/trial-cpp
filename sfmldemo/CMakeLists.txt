cmake_minimum_required(VERSION 3.24)

# 使得 所有输出都放到同个目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(SFML_USE_STATIC_STD_LIBS "USE STD STATIC LIBS." ON)

include("cmake/SFML.cmake")

FetchSFML()

project(sfmldemo)

add_subdirectory(simple)
