add_executable(woco)

add_custom_command(
    TARGET woco
    PRE_BUILD
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src"
    COMMAND "${GNUWIN32_FLEX_BIN_DIR}/flex++" woco.l
    COMMENT "flex woco"
)

target_sources(
    woco
    PRIVATE
    "src/main.cpp"
)

add_dependencies(woco flex)
