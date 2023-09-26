include(ExternalProject)

# 下载工具
function(
    GnuWin32_DownloadBison
)
    message(STATUS "GnuWin32 bison bin download start.")
    set(GNUWIN32_BISON_DIR "${CMAKE_BINARY_DIR}/bison")
    set(GNUWIN32_BISON_BIN_DIR "${CMAKE_BINARY_DIR}/bison_bin")
    set(GNUWIN32_BISON_DEP_DIR "${CMAKE_BINARY_DIR}/bison_dep")

    ExternalProject_Add(
        bison_bin

        # 以下链接可能会变
        URL https://zenlayer.dl.sourceforge.net/project/gnuwin32/bison/2.4.1/bison-2.4.1-bin.zip # 主体

        SOURCE_DIR ${GNUWIN32_BISON_BIN_DIR}

        # 不配置
	    CONFIGURE_COMMAND ""
	    # 不构建
	    BUILD_COMMAND ""
	    # 不安装
	    INSTALL_COMMAND ""

        STEP_TARGETS build
	    EXCLUDE_FROM_ALL TRUE
    )
    message(STATUS "GnuWin32 bison bin download final.")

    message(STATUS "GnuWin32 bison dep download start.")
    ExternalProject_Add(
        bison_dep
        # 以下链接可能会变
        URL https://zenlayer.dl.sourceforge.net/project/gnuwin32/bison/2.4.1/bison-2.4.1-dep.zip # 依赖

        SOURCE_DIR ${GNUWIN32_BISON_DEP_DIR}

        # 不配置
	    CONFIGURE_COMMAND ""
	    # 不构建
	    BUILD_COMMAND ""
	    # 不安装
	    INSTALL_COMMAND ""

        STEP_TARGETS build
	    EXCLUDE_FROM_ALL TRUE
    )
    add_custom_target(
        bison
        COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory" "${GNUWIN32_BISON_BIN_DIR}/bin" "${GNUWIN32_BISON_DIR}"
        COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory" "${GNUWIN32_BISON_DEP_DIR}/bin" "${GNUWIN32_BISON_DIR}"
        DEPENDS bison_bin bison_dep
    )
    message(STATUS "GnuWin32 bison dep download final.")
endfunction()

# 执行代码生成

function(
    GnuWin32_Bison
)
    message(STATUS "bison to")
endfunction()
