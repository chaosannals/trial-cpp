add_executable(wocopp)

# 目前 flex++ 不支持 windows 下开发，使用了一堆 linux 特有的东西。

set(WOCOPP_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/inc")
set(WOCOPP_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
message(STATUS "wocopp src dir: ${WOCOPP_SRC_DIR}")

add_custom_target(
    wocopp_gencode
    DEPENDS flex
)

add_custom_command(
    TARGET wocopp_gencode
    PRE_BUILD
    WORKING_DIRECTORY "${WOCOPP_SRC_DIR}"
    BYPRODUCTS "${WOCOPP_SRC_DIR}/lex.yy.cc"
    COMMAND "${GNUWIN32_FLEX_BIN_DIR}/flex++" wocopp.l
    COMMENT "flex++ wocopp"
)

target_sources(
    wocopp
    PRIVATE
    "src/main.cpp"
    # "${WOCOPP_SRC_DIR}/lex.yy.cc"
)

if (MSVC)
    target_include_directories(
        wocopp
        PRIVATE
        "${WOCOPP_INC_DIR}"
    )
endif()

add_dependencies(
    wocopp
    wocopp_gencode
)
