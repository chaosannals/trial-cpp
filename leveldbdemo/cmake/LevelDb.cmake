include(FetchContent)

function(FetchLevelDb)
    FetchContent_Declare(
        leveldb
        GIT_REPOSITORY git@github.com:google/leveldb.git
        GIT_TAG main # v1.23
        GIT_SHALLOW ON # 浅克隆，git 参数加 --depth=1
        GIT_PROGRESS ON # 打印下载进度
        # submodules 默认会拉，就是被墙了，会拉失败。
        # GIT_SUBMODULES third_party/googletest third_party/benchmark
    )
    FetchContent_MakeAvailable(leveldb)
    set(LEVELDB_SRC_DIR "${leveldb_SOURCE_DIR}")
    set(LEVELDB_SRC_DIR "${leveldb_SOURCE_DIR}" PARENT_SCOPE)
    message(STATUS "[leveldb] ${LEVELDB_SRC_DIR}")

endfunction()
