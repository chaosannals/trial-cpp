cmake_minimum_required(VERSION 3.9.6...3.15.0)
project(sshclient LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
   if (MSVC)
      # 静态运行库 MT
      if (VS_LINK_STATIC_MT)
         set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
         message(STATUS "msvc MT , element md")
      endif()
   endif()
endif()

set(ELEMENTS_ROOT ${PROJECT_SOURCE_DIR}/lib/elements)

option(VS_LINK_STATIC_MT "static link mt." OFF)

# Make sure ELEMENTS_ROOT is an absolute path to add to the CMake module path
get_filename_component(ELEMENTS_ROOT "${ELEMENTS_ROOT}" ABSOLUTE)
set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${ELEMENTS_ROOT}/cmake")

# If we are building outside the project, you need to set ELEMENTS_ROOT:
if (NOT ELEMENTS_BUILD_EXAMPLES)
   include(ElementsConfigCommon)
   set(ELEMENTS_BUILD_EXAMPLES OFF)
   add_subdirectory(${ELEMENTS_ROOT} elements)
endif()

set(ELEMENTS_APP_PROJECT "sshclient")
set(ELEMENTS_APP_TITLE "SSH Client")
set(ELEMENTS_APP_COPYRIGHT "Copyright (c) 2016-2020 Joel de Guzman")
set(ELEMENTS_APP_ID "com.cycfi.empty-starter")
set(ELEMENTS_APP_VERSION "1.0")

set(ELEMENTS_APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
file(GLOB SSHCLIENT_VIEW_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/view/*.cpp)
file(GLOB SSHCLIENT_VIEW_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/view/*.h)
list(APPEND ELEMENTS_APP_SOURCES ${SSHCLIENT_VIEW_SOURCES})
list(APPEND ELEMENTS_APP_SOURCES ${SSHCLIENT_VIEW_HEADERS})
# message(STATUS ${ELEMENTS_APP_SOURCES})

include(AppIcon)
include(ElementsConfigApp)

source_group("Source Files/view" FILES ${SSHCLIENT_VIEW_SOURCES})
source_group("Header Files/view" FILES ${SSHCLIENT_VIEW_HEADERS})
