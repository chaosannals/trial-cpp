add_executable(tcpdemo)

target_sources(
    tcpdemo
    PRIVATE
    "main.cpp"
)

set_target_properties(
    tcpdemo
    PROPERTIES
	CXX_STANDARD 20
)

target_link_libraries(
    tcpdemo
    PRIVATE
    #uv # 动态库
    uv_a # 静态库
)
