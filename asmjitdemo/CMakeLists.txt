cmake_minimum_required(VERSION 3.24)

include(FetchContent)
include("./cmake/AsmJitBuild.cmake")

set(ASMJIT_SRC_DIR "${CMAKE_CURRENT_BINARY_DIR}/asmjit_src")

project(asmjitdemo)

CloneAsmJitTo(${ASMJIT_SRC_DIR})

add_subdirectory(simple)
