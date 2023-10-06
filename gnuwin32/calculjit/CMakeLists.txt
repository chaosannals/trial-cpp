add_executable(calculjit)

include(FetchContent)

FetchContent_Declare(
	asmjit
	GIT_REPOSITORY git@github.com:asmjit/asmjit.git
    #GIT_REPOSITORY "https://gitclone.com/github.com/asmjit/asmjit"
    GIT_TAG 51b10b19b6631434d3f9ad536a6fb140944a36d2 # 镜像站 gitclone 没有早期的提交，写这个 hash 必须用 github 链接
	#GIT_TAG master
)
FetchContent_MakeAvailable(asmjit)
target_link_libraries(calculjit AsmJit::AsmJit)

set(CALCULJIT_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_custom_target(
    calculjit_gencode
    DEPENDS flex bison
)

add_custom_command(
    TARGET calculjit_gencode
    PRE_BUILD
    WORKING_DIRECTORY ${CALCULJIT_SRC_DIR}
    BYPRODUCTS "${CALCULJIT_SRC_DIR}/lex.yy.c"
    COMMAND "${GNUWIN32_FLEX_BIN_DIR}/flex" calculjit.l
    COMMENT "flex calculjit"
)


add_custom_command(
    TARGET calculjit_gencode
    PRE_BUILD
    WORKING_DIRECTORY ${CALCULJIT_SRC_DIR}
    BYPRODUCTS "${CALCULJIT_SRC_DIR}/calculjit.tab.h" "${CALCULJIT_SRC_DIR}/calculjit.tab.c"

    # -E env 设置了当前 预设好的 PATH 给 此自定义命令，详见 GnuWin32Bison.cmake 文件
    COMMAND ${CMAKE_COMMAND} -E env "PATH=$ENV{PATH}" bison -d calculjit.y
    COMMENT "bison calculjit"
)

target_sources(
    calculjit
    PRIVATE
    "src/main.cpp"
    "src/calculjit.c"
    "src/lex.yy.c"
    "${CALCULJIT_SRC_DIR}/calculjit.tab.c")

add_dependencies(
    calculjit
    calculjit_gencode
)
