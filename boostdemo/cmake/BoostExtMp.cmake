function(FetchBoostExtMp)
    FetchContent_Declare(
        boost_ext_mp
        GIT_REPOSITORY git@github.com:boost-ext/mp.git
        # GIT_TAG v1.0.0
        GIT_TAG main
        GIT_SHALLOW ON # 浅克隆，git 参数加 --depth=1
        GIT_PROGRESS ON # 打印下载进度
    )
    FetchContent_Populate(boost_ext_mp)
    set(BOOST_EXT_MP_SRC_DIR "${boost_ext_mp_SOURCE_DIR}")
    set(BOOST_EXT_MP_SRC_DIR "${boost_ext_mp_SOURCE_DIR}" PARENT_SCOPE)
    message(STATUS "[boost_ext_mp] ${BOOST_EXT_MP_SRC_DIR}")
endfunction()
