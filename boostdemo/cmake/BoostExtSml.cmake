function(FetchBoostExtSml)
    FetchContent_Declare(
        boost_ext_sml
        GIT_REPOSITORY git@github.com:boost-ext/sml.git
        GIT_TAG v1.1.11
        GIT_SHALLOW ON # 浅克隆，git 参数加 --depth=1
        GIT_PROGRESS ON # 打印下载进度
    )
    FetchContent_MakeAvailable(boost_ext_sml)
    set(BOOST_EXT_SML_SRC_DIR "${boost_ext_sml_SOURCE_DIR}")
    set(BOOST_EXT_SML_SRC_DIR "${boost_ext_sml_SOURCE_DIR}" PARENT_SCOPE)
    message(STATUS "[boost_ext_sml] ${BOOST_EXT_SML_SRC_DIR}")
endfunction()
