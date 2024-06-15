add_executable(fsdemo)

target_sources(
    fsdemo
    PRIVATE
    "main.cpp"
)

set_target_properties(
    fsdemo
    PROPERTIES
	CXX_STANDARD 20
)

target_link_libraries(
    fsdemo
    PRIVATE
    #uv # 动态库
    uv_a # 静态库
)
