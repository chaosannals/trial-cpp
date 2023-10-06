add_executable(jumbtabledemo)

target_sources(
    jumbtabledemo
    PRIVATE
    "src/main.cpp"
)

target_link_libraries(
    jumbtabledemo
    AsmJit::AsmJit
)
