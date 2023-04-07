cmake_minimum_required(VERSION 3.24)

include(FetchContent)

project(slintdemo LANGUAGES CXX)

# 引入 Slint
FetchContent_Declare(
    Slint
    GIT_REPOSITORY git@github.com:slint-ui/slint.git
    # `release/1` will auto-upgrade to the latest Slint >= 1.0.0 and < 2.0.0
    # `release/1.0` will auto-upgrade to the latest Slint >= 1.0.0 and < 1.1.0
    GIT_TAG release/1
    SOURCE_SUBDIR api/cpp
)
FetchContent_MakeAvailable(Slint)

add_executable(slintdemo)

target_sources(
    slintdemo
    PRIVATE
    "src/main.cpp"
)

# 用户生成 .h 文件，生成后会自动把生成目录添加进 TARGET 的引入目录列表。
slint_target_sources(
    slintdemo
    "src/ui/slintdemo_ui.slint" # 修改路径会有缓存问题，清除，生成物都只保留 <basename>.h  不可重名。
)

target_link_libraries(slintdemo PRIVATE Slint::Slint)

if (WIN32)
    # 在 Windows, 复制 Slint DLL
    add_custom_command(
        TARGET slintdemo
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:slintdemo> $<TARGET_FILE_DIR:slintdemo> COMMAND_EXPAND_LISTS
    )
endif()