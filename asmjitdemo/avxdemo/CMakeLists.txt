add_executable(avxdemo)

target_sources(
    avxdemo
    PRIVATE
    "src/main.cpp"
)

target_link_libraries(
    avxdemo
    AsmJit::AsmJit
)
