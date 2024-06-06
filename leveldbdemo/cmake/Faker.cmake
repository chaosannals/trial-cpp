include(FetchContent)

function(FetchFaker)
    # 指定编译器使用 utf-8，非 utf8-bom 的 utf8 源码， 中文 VS 默认识别成 GBK, 会导致部分库编码识别错误。
    # 在引入这个库前，项目开始时，要提前用 add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>") 配置
    # 这个库源码是 utf-8 ,但是缺少 bom ，导致被 VS 识别成 GBK 字符集。
    FetchContent_Declare(
        faker
        GIT_REPOSITORY git@github.com:cieslarmichal/faker-cxx.git
        # GIT_TAG v1.0.0 #此版本依赖的测试库 gtest 在和 leveldb 同时使用时版本号冲突。
        #GIT_TAG main #主分支没有卡住版本，一直是最新，这个库构建每个版本都有点不同。
        GIT_TAG d1ccb72dabb249ee4b2a288ae96d55e61b12175b # 目前只解决这个版本的引入。其他版本要自行解决。
        GIT_SHALLOW ON # 浅克隆，git 参数加 --depth=1
        GIT_PROGRESS ON # 打印下载进度
        # 把 submodule 里面的 https 换成 ssh 的，国内比较大几率能拉成功。
        # 例如把 https://github.com/google/googletest.git 换成 git@github.com:google/googletest.git
        # GIT_SUBMODULES 默认会拉，就是被墙了，会拉失败。

        # 指定编译参数 ，无效。
        # COMPILE_OPTIONS "$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>"
        # 指定编译参数 ，无效。
        # INTERFACE_COMPILE_OPTIONS "$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>"
    )
    FetchContent_MakeAvailable(faker)

    # FetchContent 的不属于 project 的 target, 不可以通过 target 修改 target 属性。
    # set_target_properties(faker-cxx::faker-cxx PROPERTIES INTERFACE_COMPILE_OPTIONS "$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

    # FetchContent 的不属于 project 的 target, 不可以通过 target 修改 编译参数。
    #target_compile_options(
    #    faker
    #    PUBLIC
    #    "$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>"
    #)
    set(FAKER_SRC_DIR "${faker_SOURCE_DIR}")
    set(FAKER_SRC_DIR "${faker_SOURCE_DIR}" PARENT_SCOPE)
    message(STATUS "[faker] ${FAKER_SRC_DIR}")
endfunction()
