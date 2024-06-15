include(FetchContent)

function(FetchLibuv)
    FetchContent_Declare(
        libuv
        GIT_REPOSITORY git@github.com:libuv/libuv.git
        GIT_TAG v1.48.0 # 
        GIT_SHALLOW ON # 浅克隆，git 参数加 --depth=1
        GIT_PROGRESS ON # 打印下载进度
    )
    FetchContent_MakeAvailable(libuv)
    set(LIBUV_SRC_DIR "${libuv_SOURCE_DIR}")
    set(LIBUV_SRC_DIR "${libuv_SOURCE_DIR}" PARENT_SCOPE)
    message(STATUS "[libuv] ${LIBUV_SRC_DIR}")


endfunction()
