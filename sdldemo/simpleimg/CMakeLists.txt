if (MSVC)
    add_executable(simpleimg WIN32)
else()
    add_executable(simpleimg)
endif()

include("../cmake/ImportSDL.cmake")

target_sources(
    simpleimg
    PRIVATE
    "src/main.cpp"
)

# 因为墙 SDL2Image 只能用二进制文件。
# 因为 SDL2Image 是二进制文件，官方没有打包调试版本，所以只能用发布模式运行。
if (CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    set(DEMO_SDL2_DLL_NAME "SDL2d.dll")
else()
    set(DEMO_SDL2_DLL_NAME "SDL2.dll")
endif()


# 复制 DLL
set(DEMO_SDL2_DLL_PATH "${SDL2_BINARY_DIR}/${DEMO_SDL2_DLL_NAME}")
message(STATUS "[sdl2] dll path: ${DEMO_SDL2_DLL_PATH}")
add_custom_command(
	TARGET simpleimg
	POST_BUILD
    COMMAND "${CMAKE_COMMAND}" "-E" "copy" "${DEMO_SDL2_DLL_PATH}" "${CMAKE_CURRENT_BINARY_DIR}"
	COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory" "${CMAKE_CURRENT_SOURCE_DIR}/res/" "${CMAKE_CURRENT_BINARY_DIR}"
)

# 符合 FetchContent 的库都会导出不需要这句，target_link_libraries 就会导入，SDL2 没有自行导出。
# 单独引入，全局引入的 include_directories 好像无效。
# 而且这样引入还和 安装版的不太一样，不是在 SDL2/SDL.h 而是 SDL.h ，少了个目录。
target_include_directories(
    simpleimg
    PRIVATE
    "${SDL2_SOURCE_DIR}/include"
)

target_link_libraries(
    simpleimg
    SDL2::SDL2 # 因为要加载 SDL2Image 二进制只能是动态的。
    SDL2::SDL2main
)

LinkSDL2Image(simpleimg)
