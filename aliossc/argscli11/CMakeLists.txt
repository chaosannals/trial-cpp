add_executable(argscli11)

target_sources(
    argscli11
    PRIVATE
    "src/main.cpp"
)

target_link_libraries(
    argscli11
    CLI11::CLI11
)
