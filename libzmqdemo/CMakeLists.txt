cmake_minimum_required(VERSION 3.24)

include("cmake/Catch2.cmake")
include("cmake/Libzmq.cmake") # C 的
include("cmake/Cppzmq.cmake") # cpp 封装，依赖 C 的 LIBZMQ

FetchCatch2() # 单元测试框架
FetchLibzmq() # C 的
FetchCppzmq() # cpp 封装，依赖 C 的 LIBZMQ

project(libzmqdemo)

add_subdirectory(simple)
add_subdirectory(cpptcpdemo)
