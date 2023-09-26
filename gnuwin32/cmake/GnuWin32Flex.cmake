include(ExternalProject)

function(
    GnuWin32_DownloadFlex
)
    message(STATUS "GnuWin32 flex bin download start.")
    set(GNUWIN32_FLEX_DIR "${CMAKE_BINARY_DIR}/flex")
    set(GNUWIN32_FLEX_BIN_DIR "${GNUWIN32_FLEX_DIR}/bin" PARENT_SCOPE)

    ExternalProject_Add(
        flex

        # 以下链接可能会变
        URL https://zenlayer.dl.sourceforge.net/project/gnuwin32/flex/2.5.4a-1/flex-2.5.4a-1-bin.zip # 主体

        SOURCE_DIR ${GNUWIN32_FLEX_DIR}

        # 不配置
	    CONFIGURE_COMMAND ""
	    # 不构建
	    BUILD_COMMAND ""
	    # 不安装
	    INSTALL_COMMAND ""

        STEP_TARGETS build
	    EXCLUDE_FROM_ALL TRUE
    )
    message(STATUS "GnuWin32 flex bin download final.")
endfunction()

function(
    GnuWin32_Flex
    FLEX_SOURCE
    FLEX_TARGET
)

endfunction()
