function(FetchOatpp)
    FetchContent_Declare(
        oatpp
        GIT_REPOSITORY git@github.com:oatpp/oatpp.git
        GIT_TAG master # 
        GIT_SHALLOW ON # 浅克隆，git 参数加 --depth=1
        GIT_PROGRESS ON # 打印下载进度
    )
    FetchContent_MakeAvailable(oatpp)
    set(OATPP_SRC_DIR "${oatpp_SOURCE_DIR}")
    set(OATPP_SRC_DIR "${oatpp_SOURCE_DIR}" PARENT_SCOPE)
    message(STATUS "[oatpp] ${OATPP_SRC_DIR}")
endfunction()
