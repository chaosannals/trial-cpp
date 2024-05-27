cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)

# 指定编译器使用 utf-8，非 utf8-bom 的 utf8 源码， 中文 VS 默认识别成 GBK, 会导致部分库编码识别错误。
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

include("cmake/LevelDb.cmake")
include("cmake/Faker.cmake")


FetchLevelDb()
FetchFaker()

project(leveldbdemo)

add_subdirectory(simple)
