include(FetchContent)

function(
	IncludeSlintProject
)
	FetchContent_Declare(
        Slint
        GIT_REPOSITORY git@github.com:slint-ui/slint.git
        # `release/1` will auto-upgrade to the latest Slint >= 1.0.0 and < 2.0.0
        # `release/1.0` will auto-upgrade to the latest Slint >= 1.0.0 and < 1.1.0
        GIT_TAG release/1
        SOURCE_SUBDIR api/cpp
    )
    FetchContent_MakeAvailable(Slint)
endfunction()