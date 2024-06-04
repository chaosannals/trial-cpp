function(FetchCrow)
    FetchContent_Declare(
        crow
        GIT_REPOSITORY git@github.com:ipkn/crow.git
        GIT_TAG master # 
        GIT_SHALLOW ON # 浅克隆，git 参数加 --depth=1
        GIT_PROGRESS ON # 打印下载进度
    )
    FetchContent_MakeAvailable(crow)
    set(CROW_SRC_DIR "${crow_SOURCE_DIR}")
    set(CROW_SRC_DIR "${crow_SOURCE_DIR}" PARENT_SCOPE)
    message(STATUS "[crow] ${CROW_SRC_DIR}")
endfunction()
