add_executable(calcul)

set(CALCUL_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_custom_target(
    calcul_gencode
    DEPENDS flex bison
)

add_custom_command(
    TARGET calcul_gencode
    PRE_BUILD
    WORKING_DIRECTORY ${CALCUL_SRC_DIR}
    BYPRODUCTS "${CALCUL_SRC_DIR}/lex.yy.c"
    COMMAND "${GNUWIN32_FLEX_BIN_DIR}/flex" calcul.l
    COMMENT "flex calcul"
)


add_custom_command(
    TARGET calcul_gencode
    PRE_BUILD
    WORKING_DIRECTORY ${CALCUL_SRC_DIR}
    BYPRODUCTS "${CALCUL_SRC_DIR}/calcul.tab.h" "${CALCUL_SRC_DIR}/calcul.tab.c"

    # -E env 设置了当前 预设好的 PATH 给 此自定义命令，详见 GnuWin32Bison.cmake 文件
    COMMAND ${CMAKE_COMMAND} -E env "PATH=$ENV{PATH}" bison -d calcul.y
    COMMENT "bison calcul"
)

target_sources(
    calcul
    PRIVATE
    "src/main.cpp"
    "src/calcul.c"
    "src/lex.yy.c"
    "${CALCUL_SRC_DIR}/calcul.tab.c")

add_dependencies(
    calcul
    calcul_gencode
)
