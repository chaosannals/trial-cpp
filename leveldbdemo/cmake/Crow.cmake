function(FetchCrow)
    # 目前是用全引入 boost 模式， TODO  尝试 按需引入。
    #FetchContent_Declare(
    #    asio
    #    GIT_REPOSITORY git@github.com:boostorg/asio.git
    #    GIT_TAG boost-1.85.0 # 
    #    GIT_SHALLOW ON # 浅克隆，git 参数加 --depth=1
    #    GIT_PROGRESS ON # 打印下载进度
    #)
    #FetchContent_MakeAvailable(asio)
    #set(ASIO_SRC_DIR "${asio_SOURCE_DIR}")
    #set(ASIO_SRC_DIR "${asio_SOURCE_DIR}" PARENT_SCOPE)
    #message(STATUS "[asio] ${ASIO_SRC_DIR}")

    # 此变量必须提供给 crow ，不然他报错，即使这个变量不适用，他还是报错。
    #set(ASIO_INCLUDE_DIR "${ASIO_SRC_DIR}/include/boost")
    #set(ASIO_INCLUDE_DIR "${ASIO_SRC_DIR}/include/boost" PARENT_SCOPE)
    #message(STATUS "[asio] ${ASIO_INCLUDE_DIR}")


    #FetchContent_Declare(
    #    boost_system
    #    GIT_REPOSITORY git@github.com:boostorg/system.git
    #    GIT_TAG boost-1.85.0 # 
    #    GIT_SHALLOW ON # 浅克隆，git 参数加 --depth=1
    #    GIT_PROGRESS ON # 打印下载进度
    #)
    #FetchContent_MakeAvailable(boost_system)
    #set(BOOST_SYSTEM_SRC_DIR "${boost_system_SOURCE_DIR}")
    #set(BOOST_SYSTEM_SRC_DIR "${boost_system_SOURCE_DIR}" PARENT_SCOPE)
    #message(STATUS "[boost_system] ${BOOST_SYSTEM_SRC_DIR}")
    #set(BOOST_SYSTEM_INC_DIR "${BOOST_SYSTEM_SRC_DIR}/include")
    #set(BOOST_SYSTEM_INC_DIR "${BOOST_SYSTEM_SRC_DIR}/include" PARENT_SCOPE)
    #message(STATUS "[boost_system] ${BOOST_SYSTEM_INC_DIR}")
    

    # Crow 没有规范使用 asio ，asio.hpp 是一堆 #include <boost/asio/*> ，而 Crow 是从 #include<asio/*> 。需要重复引入 asio 的 include 路径。
    FetchContent_Declare(
        crow
        GIT_REPOSITORY git@github.com:CrowCpp/Crow.git
        GIT_TAG v1.2.0 # 
        GIT_SHALLOW ON # 浅克隆，git 参数加 --depth=1
        GIT_PROGRESS ON # 打印下载进度
    )
    FetchContent_MakeAvailable(crow)
    set(CROW_SRC_DIR "${crow_SOURCE_DIR}")
    set(CROW_SRC_DIR "${crow_SOURCE_DIR}" PARENT_SCOPE)
    message(STATUS "[crow] ${CROW_SRC_DIR}")
endfunction()
