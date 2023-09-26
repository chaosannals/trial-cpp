cmake_minimum_required(VERSION 3.24)

message(STATUS "cmake bin dir: ${CMAKE_BINARY_DIR}")

include(FetchContent)
include(ExternalProject)
include("cmake/ImportAliyunOss.cmake")
include("cmake/ImportJsonCpp.cmake")
include("cmake/ImportNlohmannJson.cmake")
include("cmake/ImportCmdline.cmake")
include("cmake/ImportGflags.cmake")
include("cmake/ImportCli11.cmake")
include("cmake/ImportBlend2D.cmake")

# Ali settings TODO 去掉不必要的编译项目例如示例
# set(BUILD_SAMPLE OFF)
message(STATUS "aliyun settings. ${CMAKE_BUILD_TYPE}")

ImportAliyunOssSdk()
ImportJsonCpp()
ImportNlohmannJson()
ImportCmdline()
ImportGflags()
ImportCli11()
ImportBlend2D()

project(aliossc)
message(STATUS "project bin dir: ${PROJECT_BINARY_DIR}") # PROJECT_BINARY_DIR 必须要 project 之后

ImportAliyunOssSdk3PLib()

add_subdirectory(aliosst)
add_subdirectory(test1)
add_subdirectory(argsgflags)
add_subdirectory(argscli11)
add_subdirectory(uiblend2d)
