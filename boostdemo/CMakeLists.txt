﻿cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
include("cmake/Boost.cmake")
include("cmake/BoostExtDi.cmake")
include("cmake/BoostExtSml.cmake")
include("cmake/BoostExtMp.cmake")
include("cmake/BoostExtSml2.cmake")
include("cmake/Crow.cmake")

project(boostdemo)

FetchBoost()
FetchBoostExtDi()
FetchBoostExtSml()
FetchBoostExtMp()
FetchBoostExtSml2()
FetchCrow()

add_subdirectory(simple)
add_subdirectory(crowdemo)
add_subdirectory(didemo)
add_subdirectory(smldemo)
add_subdirectory(mpdemo)
add_subdirectory(sml2demo)
