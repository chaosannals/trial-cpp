cmake_minimum_required(VERSION 3.24)

include("cmake/ImportSDL.cmake")

project(sdldemo)

ImportSDL()

add_subdirectory(simple)
