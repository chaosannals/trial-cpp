include(FetchContent)

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
    
endfunction()
