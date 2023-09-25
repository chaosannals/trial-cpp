# 这个库用到了 git submodule 因为墙的原因，无法直接指定 submodule 下载。
# 被墙了多试试几次，或者换用代理。
# 而且这个库 必须是  MT Release （也就是 Debug 是不能链接成功的）
function(
    ImportGflags
)
    message(STATUS "import gflags start.")
    FetchContent_Declare(
        gflags
        GIT_REPOSITORY git@github.com:gflags/gflags.git
        GIT_TAG v2.2.2
    )

    FetchContent_MakeAvailable(gflags)
    message(STATUS "import gflags end.")
endfunction()
