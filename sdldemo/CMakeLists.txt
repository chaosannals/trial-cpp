cmake_minimum_required(VERSION 3.24)

include("cmake/ImportSDL.cmake")

project(sdldemo)

ImportSDL()
IncludeSDL2Image()


add_subdirectory(simple)
add_subdirectory(simpleimg)
