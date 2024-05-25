cmake_minimum_required(VERSION 3.24)

include("cmake/LevelDb.cmake")

set(CMAKE_CXX_STANDARD 20)

FetchLevelDb()

project(leveldbdemo)

add_subdirectory(simple)
