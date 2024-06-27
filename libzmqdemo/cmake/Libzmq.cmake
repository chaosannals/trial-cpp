include(FetchContent)

function(FetchLibzmq)
    FetchContent_Declare(
        libzmq
        GIT_REPOSITORY git@github.com:zeromq/libzmq.git
        GIT_TAG v4.3.5 # 这个脚本里面好像和 ninja 有点问题，切换其他工具
        # GIT_TAG master # 
        GIT_SHALLOW ON # 浅克隆，git 参数加 --depth=1
        GIT_PROGRESS ON # 打印下载进度
    )
    FetchContent_MakeAvailable(libzmq)
    set(LIBZMQ_SRC_DIR "${libzmq_SOURCE_DIR}")
    set(LIBZMQ_SRC_DIR "${libzmq_SOURCE_DIR}" PARENT_SCOPE)
    message(STATUS "[libzmq] ${LIBZMQ_SRC_DIR}")
endfunction()
