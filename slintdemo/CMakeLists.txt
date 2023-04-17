cmake_minimum_required(VERSION 3.24)

include(FetchContent)
include("./cmake/BuildSlint.cmake")

project(slintdemo LANGUAGES CXX)

IncludeSlintProject()

add_subdirectory(demo1)
