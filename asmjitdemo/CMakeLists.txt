cmake_minimum_required(VERSION 3.24)

include(FetchContent)
include("./cmake/AsmJitBuild.cmake")

# 开启静态(这样会写死，最好还是通过 CMAKE OPTIONS 指定)
set(ASMJIT_STATIC ON)
set(ASMJIT_SRC_DIR "${CMAKE_CURRENT_BINARY_DIR}/asmjit_src")

project(asmjitdemo)

CloneAsmJitTo(${ASMJIT_SRC_DIR})

add_subdirectory(simple)
add_subdirectory(funcdemo)
add_subdirectory(avxdemo)
add_subdirectory(fibdemo)

