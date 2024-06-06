cmake_minimum_required(VERSION 3.24)


include(FetchContent)
include("cmake/Boost.cmake")
include("cmake/Crow.cmake")

project(boostdemo)

FetchBoost()
FetchCrow()

add_subdirectory(simple)
add_subdirectory(crowdemo)