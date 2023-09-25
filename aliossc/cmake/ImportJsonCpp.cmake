function(
    ImportJsonCpp
)
    set(JSONCPP_DIR "${CMAKE_CURRENT_BINARY_DIR}/jsoncpp")
    set(JSONCPP_SRC_DIR "${JSONCPP_DIR}/src")
    set(JSONCPP_BUILD_DIR "${JSONCPP_DIR}/build")
    set(JSONCPP_OUT_DIR "${JSONCPP_DIR}/out")

    # 加上 PARENT_SCOPE 把这几个变量暴露给 父级作用域
    set(JSONCPP_DIR "${JSONCPP_DIR}" PARENT_SCOPE)
    set(JSONCPP_SRC_DIR "${JSONCPP_SRC_DIR}" PARENT_SCOPE)
    set(JSONCPP_BUILD_DIR "${JSONCPP_BUILD_DIR}" PARENT_SCOPE)
    set(JSONCPP_OUT_DIR "${JSONCPP_OUT_DIR}" PARENT_SCOPE)

    message(STATUS "JsonCpp dir: ${JSONCPP_DIR}")
    message(STATUS "JsonCpp src dir: ${JSONCPP_SRC_DIR}")
    message(STATUS "JsonCpp build dir: ${JSONCPP_BUILD_DIR}")
    message(STATUS "JsonCpp out dir: ${JSONCPP_OUT_DIR}")

    ExternalProject_Add(
        JsonCpp

        # github 有墙，使用镜像链接。
        GIT_REPOSITORY "https://gitclone.com/github.com/open-source-parsers/jsoncpp" 
        # GIT_REPOSITORY "git@github.com:open-source-parsers/jsoncpp.git"
        GIT_TAG 1.9.5

        SOURCE_DIR "${JSONCPP_SRC_DIR}"

        CONFIGURE_COMMAND "${CMAKE_COMMAND}" -S "${JSONCPP_SRC_DIR}" -B "${JSONCPP_BUILD_DIR}"
	    BUILD_COMMAND "${CMAKE_COMMAND}" "--build" "${JSONCPP_BUILD_DIR}" "--config" "${CMAKE_BUILD_TYPE}"

        INSTALL_COMMAND "${CMAKE_COMMAND}" "--install" "${JSONCPP_BUILD_DIR}" "--config" "${CMAKE_BUILD_TYPE}" "--prefix" "${JSONCPP_OUT_DIR}"

        STEP_TARGETS build
	    EXCLUDE_FROM_ALL TRUE
    )

    set(JSONCPP_DLL_DIR "${JSONCPP_OUT_DIR}/bin")
    set(JSONCPP_DLL_DIR "${JSONCPP_DLL_DIR}" PARENT_SCOPE)
endfunction()
