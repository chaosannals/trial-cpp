add_executable(fibdemo)

target_sources(
    fibdemo
    PRIVATE
    "src/main.cpp"
)

target_link_libraries(
    fibdemo
    AsmJit::AsmJit
)
