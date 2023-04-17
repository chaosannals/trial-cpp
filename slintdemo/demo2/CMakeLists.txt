add_executable(slintdemo2)

target_sources(
    slintdemo2
    PRIVATE
    "src/main.cpp"
)

# 用户生成 .h 文件，生成后会自动把生成目录添加进 TARGET 的引入目录列表。
file(GLOB DEMO2_SLINT_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/ui/*.slint")

message(STATUS "demo2 slint files: ${CMAKE_CURRENT_SOURCE_DIR} ${DEMO2_SLINT_FILES}")

slint_target_sources(
    slintdemo2
    # "src/ui/demo2_ui.slint" # 修改路径会有缓存问题，清除，生成物都只保留 <basename>.h  不可重名。
    ${DEMO2_SLINT_FILES}
)


target_link_libraries(slintdemo2 PRIVATE Slint::Slint)

if (WIN32)
    # 在 Windows, 复制 Slint DLL
    add_custom_command(
        TARGET slintdemo2
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:slintdemo2> $<TARGET_FILE_DIR:slintdemo2> COMMAND_EXPAND_LISTS
    )
endif()