function(
	ImportAliyunOssSdk
)
    # 函数内作用域变量
	set(ALIYUN_OSS_SDK_DIR "${CMAKE_BINARY_DIR}/aliyunossdk")
    set(ALIYUN_OSS_SDK_SRC_DIR "${ALIYUN_OSS_SDK_DIR}/src")
    set(ALIYUN_OSS_SDK_BUILD_DIR "${ALIYUN_OSS_SDK_DIR}/build")
    set(ALIYUN_OSS_SDK_OUT_DIR "${ALIYUN_OSS_SDK_DIR}/out")

    # 加上 PARENT_SCOPE 把这几个变量暴露给 父级作用域
    set(ALIYUN_OSS_SDK_DIR "${CMAKE_BINARY_DIR}/aliyunossdk" PARENT_SCOPE)
    set(ALIYUN_OSS_SDK_SRC_DIR "${ALIYUN_OSS_SDK_DIR}/src" PARENT_SCOPE)
    set(ALIYUN_OSS_SDK_BUILD_DIR "${ALIYUN_OSS_SDK_DIR}/build" PARENT_SCOPE)
    set(ALIYUN_OSS_SDK_OUT_DIR "${ALIYUN_OSS_SDK_DIR}/out" PARENT_SCOPE)

    message(STATUS "oss sdk dir: ${ALIYUN_OSS_SDK_DIR}")
    message(STATUS "oss sdk src dir: ${ALIYUN_OSS_SDK_SRC_DIR}")
    message(STATUS "oss sdk build dir: ${ALIYUN_OSS_SDK_BUILD_DIR}")
    message(STATUS "oss sdk out dir: ${ALIYUN_OSS_SDK_OUT_DIR}")

    ExternalProject_Add(
        AliYunOssSdk

        GIT_REPOSITORY git@github.com:aliyun/aliyun-oss-cpp-sdk.git
        GIT_TAG 1.9.1
    
        SOURCE_DIR "${ALIYUN_OSS_SDK_SRC_DIR}"

        CONFIGURE_COMMAND "${CMAKE_COMMAND}" -S "${ALIYUN_OSS_SDK_SRC_DIR}" -B "${ALIYUN_OSS_SDK_BUILD_DIR}"
	    BUILD_COMMAND "${CMAKE_COMMAND}" "--build" "${ALIYUN_OSS_SDK_BUILD_DIR}" "--config" "${CMAKE_BUILD_TYPE}"

        # 执行安装 ${CMAKE_MAKE_PROGRAM} 是 ninja 、 make 、nmake 之流。
        INSTALL_COMMAND "${CMAKE_COMMAND}" "--install" "${ALIYUN_OSS_SDK_BUILD_DIR}" "--config" "${CMAKE_BUILD_TYPE}" "--prefix" "${ALIYUN_OSS_SDK_OUT_DIR}"

        # 配置 build 阶段就生成目标并安装
	    STEP_TARGETS build
	    EXCLUDE_FROM_ALL TRUE
    )

endfunction()

function(
    ImportAliyunOssSdk3PLib
)
    # 这个只能区分 VC 的 cl.exe ，刚好阿里的库第三方也只给 Windows 的。而且必须在 project 之后调用，不然不知道生成物是不是 MSVC
    if (MSVC)
	    if(CMAKE_CL_64)
		    set(ALIYUN_OSS_3P_DLL_DIR "${ALIYUN_OSS_SDK_SRC_DIR}/third_party/lib/x64")
	    else()
		    set(ALIYUN_OSS_3P_DLL_DIR "${ALIYUN_OSS_SDK_SRC_DIR}/third_party/lib/Win32")
	    endif()
    endif()

    message(STATUS "ali oss 3p dll dir: ${ALIYUN_OSS_3P_DLL_DIR}")
    file(GLOB ALIYUN_OSS_3P_DLL "${ALIYUN_OSS_3P_DLL_DIR}/*.dll")
    message(STATUS "ali oss 3p dlls: ${ALIYUN_OSS_3P_DLL}")

    # 导出到父级作用域
    set(ALIYUN_OSS_3P_DLL_DIR "${ALIYUN_OSS_3P_DLL_DIR}" PARENT_SCOPE)
endfunction()
