add_executable(didemo)

target_sources(
    didemo
    PRIVATE
    "main.cpp"
)

target_link_libraries(
    didemo
    PRIVATE
    Boost.DI
)
