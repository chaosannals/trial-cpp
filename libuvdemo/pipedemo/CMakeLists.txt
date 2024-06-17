add_executable(pipedemo)

target_sources(
    pipedemo
    PRIVATE
    "main.cpp"
)

set_target_properties(
    pipedemo
    PROPERTIES
	CXX_STANDARD 20
)

target_link_libraries(
    pipedemo
    PRIVATE
    #uv # 动态库
    uv_a # 静态库
)
