cmake_minimum_required(VERSION 3.24)

include(FetchContent)

project(slintdemo LANGUAGES CXX)

# ÒýÈë Slint
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
    "main.cpp"
)

slint_target_sources(slintdemo slintdemo_ui.slint)
target_link_libraries(slintdemo PRIVATE Slint::Slint)
# On Windows, copy the Slint DLL next to the application binary so that it's found.
if (WIN32)
    add_custom_command(
        TARGET slintdemo
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:slintdemo> $<TARGET_FILE_DIR:slintdemo> COMMAND_EXPAND_LISTS
    )
endif()