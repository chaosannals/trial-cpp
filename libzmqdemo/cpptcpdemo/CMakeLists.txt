add_executable(cpptcpdemo)

target_sources(
    cpptcpdemo
    PRIVATE
    "main.cpp"
)

target_link_libraries(
    cpptcpdemo
    PRIVATE
    cppzmq-static
)

set_target_properties(
    cpptcpdemo
    PROPERTIES
	CXX_STANDARD 20
)
