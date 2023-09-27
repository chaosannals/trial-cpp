add_executable(woco)

set(WOCO_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
message(STATUS "woco src dir: ${WOCO_SRC_DIR}")

add_custom_target(
    woco_gencode
    DEPENDS flex
)

add_custom_command(
    TARGET woco_gencode
    PRE_BUILD
    WORKING_DIRECTORY "${WOCO_SRC_DIR}"
    BYPRODUCTS "${WOCO_SRC_DIR}/lex.yy.c"
    COMMAND "${GNUWIN32_FLEX_BIN_DIR}/flex" woco.l
    COMMENT "flex woco"
)

target_sources(
    woco
    PUBLIC
    "${WOCO_SRC_DIR}/lex.yy.c"
    "src/main.cpp"
)

add_dependencies(
    woco
    woco_gencode
)
