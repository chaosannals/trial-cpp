cmake_minimum_required(VERSION 3.20)

option(VS_LINK_STATIC_MT "static link mt." ON)

project(asiodemo LANGUAGES CXX)

if (WIN32)
   if (MSVC)

      # 静态运行库 MT
      if (VS_LINK_STATIC_MT)
         set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
         message(STATUS "msvc MT , element md")
      endif()
   endif()
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CORE_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../libs/core/include)
set(SYSTEM_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../libs/system/include)
set(CONFIG_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../libs/config/include)
set(REGEX_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../libs/regex/include)
set(PREDEF_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../libs/predef/include)
set(UTILITY_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../libs/utility/include)
set(THROW_EXCEPTION_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../libs/throw_exception/include)
set(DATE_TIME_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../libs/date_time/include)
set(SMART_PTR_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../libs/smart_ptr/include)
set(STATIC_ASSERT_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../libs/static_assert/include)
set(ASSERT_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../libs/assert/include)
set(WINAPI_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../libs/winapi/include)
set(ASIO_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../libs/asio/include)
set(BIND_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../libs/bind/include)
set(TYPE_TRAITS_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../libs/type_traits/include)
set(NUMERIC_CONVERSION_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../libs/numeric_conversion/include)
set(MPL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../libs/mpl/include)
set(PREPROCESSOR_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../libs/preprocessor/include)
set(ALIGN_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../libs/align/include)

add_executable(asiodemo)

target_sources(
    asiodemo
    PRIVATE "main.cpp"
)

if (WIN32)
    target_link_libraries(
        asiodemo
        PUBLIC -lwsock32 -lws2_32
    )
endif()

target_include_directories(
    asiodemo
    PUBLIC ${CORE_INCLUDE}
    PUBLIC ${SYSTEM_INCLUDE}
    PUBLIC ${CONFIG_INCLUDE}
    PUBLIC ${REGEX_INCLUDE}
    PUBLIC ${PREDEF_INCLUDE}
    PUBLIC ${UTILITY_INCLUDE}
    PUBLIC ${THROW_EXCEPTION_INCLUDE}
    PUBLIC ${DATE_TIME_INCLUDE}
    PUBLIC ${SMART_PTR_INCLUDE}
    PUBLIC ${STATIC_ASSERT_INCLUDE}
    PUBLIC ${ASSERT_INCLUDE}
    PUBLIC ${WINAPI_INCLUDE}
    PUBLIC ${ASIO_INCLUDE}
    PUBLIC ${BIND_INCLUDE}
    PUBLIC ${TYPE_TRAITS_INCLUDE}
    PUBLIC ${NUMERIC_CONVERSION_INCLUDE}
    PUBLIC ${MPL_INCLUDE}
    PUBLIC ${PREPROCESSOR_INCLUDE}
    PUBLIC ${ALIGN_INCLUDE}
)
