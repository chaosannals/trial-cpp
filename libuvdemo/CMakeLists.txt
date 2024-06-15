cmake_minimum_required(VERSION 3.24)

option(BUILD_SHARED_LIBS "uv shared." OFF)

include("cmake/Libuv.cmake")

FetchLibuv()

project(libuvdemo)

add_subdirectory(simple)
add_subdirectory(idledemo)
add_subdirectory(fsdemo)
