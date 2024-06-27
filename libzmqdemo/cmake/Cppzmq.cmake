include(FetchContent)

function(FetchCppzmq)
    FetchContent_Declare(
        cppzmq
        GIT_REPOSITORY git@github.com:zeromq/cppzmq.git
        GIT_TAG v4.10.0 # 
        # GIT_TAG master # 
        GIT_SHALLOW ON # 浅克隆，git 参数加 --depth=1
        GIT_PROGRESS ON # 打印下载进度
    )
    FetchContent_MakeAvailable(cppzmq)
    set(CPPZMQ_SRC_DIR "${cppzmq_SOURCE_DIR}")
    set(CPPZMQ_SRC_DIR "${cppzmq_SOURCE_DIR}" PARENT_SCOPE)
    message(STATUS "[cppzmq] ${CPPZMQ_SRC_DIR}")
endfunction()
