add_executable(simple)

target_sources(
    simple
    PRIVATE
    "main.cpp"
)

if (MSVC)
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
