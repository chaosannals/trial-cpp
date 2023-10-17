include(FetchContent)

set(DEMO_SDL2IAMGE_DIR "${CMAKE_SOURCE_DIR}/libs/SDL2_image-2.6.3")
set(DEMO_SDL2IMAGE_INC_DIR "${DEMO_SDL2IAMGE_DIR}/include")

message(STATUS "[sdl2] image dir: ${DEMO_SDL2IAMGE_DIR}")
message(STATUS "[sdl2] image inc dir: ${DEMO_SDL2IMAGE_INC_DIR}")


function(
    ImportSDL
)
    FetchContent_Declare(
        SDL2
        GIT_REPOSITORY "git@github.com:libsdl-org/SDL.git"
        GIT_TAG        "release-2.28.4"
        GIT_SHALLOW ON # 浅克隆，git 参数加 --depth=1
        GIT_PROGRESS ON # 打印下载进度
    )
    FetchContent_MakeAvailable(SDL2)
    message(STATUS "[sdldemo] ${SDL2_SOURCE_DIR}/include")
endfunction()

function(
    ImportSDLImage
)
    # 有很多依赖的 git submodule 所以需要翻墙。
    # 可以尝试到目录下 git submodule update 然后一个一个去 git clone 一遍。再执行 git sbumodule update 好像有缓存机制。
    # 不然直接执行，大概率会失败。
    # 也有建议直接改 .gitmodule 配置 链接到镜像的，不过这样也很脏，而且 FetchContent 每次都会删掉重新拉，所以改这个不适合 cmake
    FetchContent_Declare(
        SDL2image
        GIT_REPOSITORY "git@github.com:libsdl-org/SDL_image.git"
        GIT_TAG        "release-2.6.3"
        GIT_SHALLOW ON # 浅克隆，git 参数加 --depth=1
        GIT_PROGRESS ON # 打印下载进度
    )
    FetchContent_MakeAvailable(SDL2image)
    message(STATUS "[sdldemo] ${SDL2IMAGE_INCLUDE_DIRS}/include")
endfunction()

function(
    IncludeSDL2Image
)
    if (CMAKE_CL_64)
        set(DEMO_SDL2IMAGE_LIB_DIR "${DEMO_SDL2IAMGE_DIR}/lib/x64")
    else()
        set(DEMO_SDL2IMAGE_LIB_DIR "${DEMO_SDL2IAMGE_DIR}/lib/x86")
    endif()
    message(STATUS "[sdl2] image lib dir: ${DEMO_SDL2IMAGE_LIB_DIR}")
    include_directories(${DEMO_SDL2IMAGE_INC_DIR})
    link_directories(${DEMO_SDL2IMAGE_LIB_DIR})
endfunction()

function(
    LinkSDL2Image
    TARGET_NAME
)
    # 复制 DLL
    if (CMAKE_CL_64)
        set(DEMO_SDL2IMAGE_LIB_DIR "${DEMO_SDL2IAMGE_DIR}/lib/x64")
    else()
        set(DEMO_SDL2IMAGE_LIB_DIR "${DEMO_SDL2IAMGE_DIR}/lib/x86")
    endif()
    add_custom_command(
	    TARGET ${TARGET_NAME}
	    POST_BUILD
	    COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory" "${DEMO_SDL2IMAGE_LIB_DIR}" "${CMAKE_CURRENT_BINARY_DIR}"
    )
    target_link_libraries(${TARGET_NAME} SDL2_image.lib)
endfunction()
