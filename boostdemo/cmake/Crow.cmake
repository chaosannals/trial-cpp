function(FetchCrow)
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
