add_executable(simple)

target_sources(
    simple
    PRIVATE
    "main.cpp"
)

# 目前 libuv cmake 没有处理 win mt 。
#set_target_properties(
#    simple
#    PROPERTIES
#	MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
#)

target_link_libraries(
    simple
    PRIVATE
    #uv # 动态库
    uv_a # 静态库
)
