add_executable(tcpcli)

target_sources(
    tcpcli
    PRIVATE
    "main.cpp"
)

set_target_properties(
    tcpcli
    PROPERTIES
	CXX_STANDARD 20
)

target_link_libraries(
    tcpcli
    PRIVATE
    #uv # 动态库
    uv_a # 静态库
)
