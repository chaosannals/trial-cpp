# 目前试过 比 gflags 易用，cmdline 没人维护十几年。

function(
    ImportCli11
)
    message(STATUS "import cli11 start.")
    FetchContent_Declare(
        cli11
        GIT_REPOSITORY git@github.com:CLIUtils/CLI11.git
        GIT_TAG v2.3.2
    )

    FetchContent_MakeAvailable(cli11)
    message(STATUS "import cli11 end.")
endfunction()
