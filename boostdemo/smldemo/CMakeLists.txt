add_executable(smldemo)

target_sources(
    smldemo
    PRIVATE
    "main.cpp"
)

target_link_libraries(
    smldemo
    PRIVATE
    sml
)
