function(FetchBoostExtDi)
    FetchContent_Declare(
        boost_ext_di
        GIT_REPOSITORY git@github.com:boost-ext/di.git
        GIT_TAG cpp14 # 这个没卡住版本，只是一个兼容 cpp14 的分支
        GIT_SHALLOW ON # 浅克隆，git 参数加 --depth=1
        GIT_PROGRESS ON # 打印下载进度
    )
    FetchContent_MakeAvailable(boost_ext_di)
    set(BOOST_EXT_DI_SRC_DIR "${boost_ext_di_SOURCE_DIR}")
    set(BOOST_EXT_DI_SRC_DIR "${boost_ext_di_SOURCE_DIR}" PARENT_SCOPE)
    message(STATUS "[boost_ext_di] ${BOOST_EXT_DI_SRC_DIR}")
endfunction()
