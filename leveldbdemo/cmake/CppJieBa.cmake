function(FetchCppJieBa)
    # 这个项目没有规范使用 Cmake ，不过源码全是头文件，只要拉代码引入 头文件即可。 
    FetchContent_Declare(
        cppjieba
        GIT_REPOSITORY git@github.com:yanyiwu/cppjieba.git
        GIT_TAG v5.1.0
        GIT_SHALLOW ON # 浅克隆，git 参数加 --depth=1
        GIT_PROGRESS ON # 打印下载进度
    )
    FetchContent_Populate(cppjieba)
    set(CPPJIEBA_SRC_DIR "${cppjieba_SOURCE_DIR}")
    set(CPPJIEBA_SRC_DIR "${cppjieba_SOURCE_DIR}" PARENT_SCOPE)
    set(CPPJIEBA_INC_DIR "${cppjieba_SOURCE_DIR}/include")
    set(CPPJIEBA_INC_DIR "${cppjieba_SOURCE_DIR}/include" PARENT_SCOPE)
    set(LIMONP_INC_DIR "${cppjieba_SOURCE_DIR}/deps/limonp/include")
    set(LIMONP_INC_DIR "${cppjieba_SOURCE_DIR}/deps/limonp/include" PARENT_SCOPE)
    message(STATUS "[cppjieba] ${CPPJIEBA_SRC_DIR}")
    message(STATUS "[cppjieba] ${CPPJIEBA_INC_DIR}")
    message(STATUS "[limonp] ${LIMONP_INC_DIR}")
endfunction()
