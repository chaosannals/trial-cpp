add_executable(simple)

target_sources(
    simple
    PRIVATE
    "main.cpp"
)

target_link_libraries(
    simple
    PRIVATE
    cppzmq-static
)

set_target_properties(
    simple
    PROPERTIES
	CXX_STANDARD 20
)
