add_executable(simple)

target_sources(
    simple
    PRIVATE
    "main.cpp"
)

if (MSVC)
    # 指定 源码字符集 UTF8，这个不必要，有.editorconfig 指定了 utf8-bom ，代码文件带了 bom 能被 VS 识别。
    #target_compile_options(
    #    simple
    #    PUBLIC
    #    "$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>"
    #    "$<$<C_COMPILER_ID:MSVC>:/source-charset:utf-8>"
    #)
    target_compile_definitions(
        simple
        PRIVATE
        "-DUNICODE"
        "-D_UNICODE"
    )
endif()

target_link_libraries(
    simple
    leveldb
    faker-cxx
)
