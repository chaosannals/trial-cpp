include(FetchContent)

function(FetchCatch2)
    FetchContent_Declare(
        catch2
        GIT_REPOSITORY git@github.com:catchorg/Catch2.git
        GIT_TAG v3.6.0 # 
        # GIT_TAG master # 
        GIT_SHALLOW ON # 浅克隆，git 参数加 --depth=1
        GIT_PROGRESS ON # 打印下载进度
    )
    FetchContent_MakeAvailable(catch2)
    set(CATCH2_SRC_DIR "${catch2_SOURCE_DIR}")
    set(CATCH2_SRC_DIR "${catch2_SOURCE_DIR}" PARENT_SCOPE)
    message(STATUS "[catch2] ${CATCH2_SRC_DIR}")
endfunction()
