function(FetchBoostExtSml2)
    FetchContent_Declare(
        boost_ext_sml2
        GIT_REPOSITORY git@github.com:boost-ext/sml2.git
        # GIT_TAG v2.0.0
        GIT_TAG main
        GIT_SHALLOW ON # 浅克隆，git 参数加 --depth=1
        GIT_PROGRESS ON # 打印下载进度
    )
    FetchContent_Populate(boost_ext_sml2)
    set(BOOST_EXT_SML2_SRC_DIR "${boost_ext_sml2_SOURCE_DIR}")
    set(BOOST_EXT_SML2_SRC_DIR "${boost_ext_sml2_SOURCE_DIR}" PARENT_SCOPE)
    message(STATUS "[boost_ext_sml2] ${BOOST_EXT_SML2_SRC_DIR}")
endfunction()
