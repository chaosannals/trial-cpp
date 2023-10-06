add_executable(stackdemo)

target_sources(
    stackdemo
    PRIVATE
    "src/main.cpp"
)

target_link_libraries(
    stackdemo
    AsmJit::AsmJit
)
