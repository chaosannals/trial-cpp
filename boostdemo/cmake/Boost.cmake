function(FetchBoost)
    FetchContent_Declare(
        boost
        GIT_REPOSITORY git@github.com:boostorg/boost.git
        GIT_TAG boost-1.85.0 # 
        GIT_SHALLOW ON # 浅克隆，git 参数加 --depth=1
        GIT_PROGRESS ON # 打印下载进度
    )
    FetchContent_MakeAvailable(boost)
    set(BOOST_SRC_DIR "${boost_SOURCE_DIR}")
    set(BOOST_SRC_DIR "${boost_SOURCE_DIR}" PARENT_SCOPE)
    message(STATUS "[boost] ${BOOST_SRC_DIR}")

    # Crow 不规范使用 boost ，需要给他开小灶，设置这个变量。其实没用到。
    set(ASIO_INCLUDE_DIR "${BOOST_SRC_DIR}/libs/asio/include/boost")
    set(ASIO_INCLUDE_DIR "${BOOST_SRC_DIR}/libs/asio/include/boost" PARENT_SCOPE)
    message(STATUS "[asio] ${ASIO_INCLUDE_DIR}")
endfunction()
