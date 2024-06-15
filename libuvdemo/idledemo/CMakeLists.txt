add_executable(idledemo)

target_sources(
    idledemo
    PRIVATE
    "main.cpp"
)

target_link_libraries(
    idledemo
    PRIVATE
    #uv # 动态库
    uv_a # 静态库
)
