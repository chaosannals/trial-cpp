add_executable(eventdemo)

target_sources(
    eventdemo
    PRIVATE
    "main.cpp"
)

set_target_properties(
    eventdemo
    PROPERTIES
	CXX_STANDARD 20
)

target_link_libraries(
    eventdemo
    PRIVATE
    #uv # 动态库
    uv_a # 静态库
)
