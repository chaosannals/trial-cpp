add_executable(simple)

target_sources(
    simple
    PRIVATE
    "src/main.cpp"
)

# 符合 FetchContent 的库都会导出不需要这句，target_link_libraries 就会导入，SDL2 没有自行导出。
# 单独引入，全局引入的 include_directories 好像无效。
# 而且这样引入还和 安装版的不太一样，不是在 SDL2/SDL.h 而是 SDL.h ，少了个目录。
target_include_directories(
    simple
    PRIVATE
    "${SDL2_SOURCE_DIR}/include"
)

target_link_libraries(
    simple
    SDL2::SDL2-static
    SDL2::SDL2main
)
