add_executable(extfuncdemo)

target_sources(
    extfuncdemo
    PRIVATE
    "src/main.cpp"
)

target_link_libraries(
    extfuncdemo
    AsmJit::AsmJit
)
