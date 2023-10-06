add_executable(constpooldemo)

target_sources(
    constpooldemo
    PRIVATE
    "src/main.cpp"
)

target_link_libraries(
    constpooldemo
    AsmJit::AsmJit
)
