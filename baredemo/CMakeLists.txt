cmake_minimum_required(VERSION 3.9.6...3.15.0)
project(baredemo LANGUAGES C CXX)

set(ELEMENTS_ROOT ${PROJECT_SOURCE_DIR}/lib/elements)

# Make sure ELEMENTS_ROOT is an absolute path to add to the CMake module path
get_filename_component(ELEMENTS_ROOT "${ELEMENTS_ROOT}" ABSOLUTE)
set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${ELEMENTS_ROOT}/cmake")

# If we are building outside the project, you need to set ELEMENTS_ROOT:
if (NOT ELEMENTS_BUILD_EXAMPLES)
   include(ElementsConfigCommon)
   set(ELEMENTS_BUILD_EXAMPLES OFF)
   add_subdirectory(${ELEMENTS_ROOT} elements)
endif()

set(ELEMENTS_APP_PROJECT "baredemo")
set(ELEMENTS_APP_TITLE "bare demo")
set(ELEMENTS_APP_COPYRIGHT "Copyright (c) 2016-2020 Joel de Guzman")
set(ELEMENTS_APP_ID "com.cycfi.empty-starter")
set(ELEMENTS_APP_VERSION "1.0")

set(ELEMENTS_APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
set(ELEMENTS_APP_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/res/deep_space.jpg)

if (WIN32)
   if (MSVC)
      message(STATUS "msvc ${PROJECT_SOURCE_DIR}")
      if (CMAKE_CL_64)
         message(STATUS "x64 ${PROJECT_SOURCE_DIR}")
         #link_directories(AFTER ${PROJECT_SOURCE_DIR}/lib/libmatoya/winx64)
         set(ELEMENTS_APP_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/lib/libmatoya/winx64)
         # bcrypt.lib d3d11.lib d3d9.lib hid.lib uuid.lib dxguid.lib opengl32.lib ws2_32.lib user32.lib gdi32.lib xinput9_1_0.lib ole32.lib shell32.lib windowscodecs.lib shlwapi.lib imm32.lib winmm.lib winhttp.lib secur32.lib crypt32.lib
         set(ELEMENTS_APP_DEPENDENCIES Bcrypt.lib ${PROJECT_SOURCE_DIR}/lib/libmatoya/winx64/matoya.lib)
      else()
         message(STATUS "x86 ${PROJECT_SOURCE_DIR}")
         #link_directories(AFTER ${PROJECT_SOURCE_DIR}/lib/libmatoya/winx32)
         set(ELEMENTS_APP_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/lib/libmatoya/winx32)
         # bcrypt.lib d3d11.lib d3d9.lib hid.lib uuid.lib dxguid.lib opengl32.lib ws2_32.lib user32.lib gdi32.lib xinput9_1_0.lib ole32.lib shell32.lib windowscodecs.lib shlwapi.lib imm32.lib winmm.lib winhttp.lib secur32.lib crypt32.lib
         set(ELEMENTS_APP_DEPENDENCIES Bcrypt.lib ${PROJECT_SOURCE_DIR}/lib/libmatoya/winx32/matoya.lib)
      endif()
   endif()
endif()

include(AppIcon)
include(ElementsConfigApp)

set_property(TARGET baredemo APPEND PROPERTY INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/lib/libmatoya/winx64)
