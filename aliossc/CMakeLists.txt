cmake_minimum_required(VERSION 3.24)

include(FetchContent)
include(ExternalProject)

set(ALIYUN_OSS_SDK_DIR "${CMAKE_CURRENT_BINARY_DIR}/aliyunossdk")
set(ALIYUN_OSS_SDK_SRC_DIR "${ALIYUN_OSS_SDK_DIR}/src")
set(ALIYUN_OSS_SDK_BUILD_DIR "${ALIYUN_OSS_SDK_DIR}/build")
set(ALIYUN_OSS_SDK_OUT_DIR "${ALIYUN_OSS_SDK_DIR}/out")

message(STATUS "oss sdk dir: ${ALIYUN_OSS_SDK_DIR}")
message(STATUS "oss sdk src dir: ${ALIYUN_OSS_SDK_SRC_DIR}")
message(STATUS "oss sdk build dir: ${ALIYUN_OSS_SDK_BUILD_DIR}")
message(STATUS "oss sdk out dir: ${ALIYUN_OSS_SDK_OUT_DIR}")

# Ali settings TODO 去掉不必要的编译项目例如示例
# set(BUILD_SAMPLE OFF)
message(STATUS "aliyun settings. ${CMAKE_BUILD_TYPE}")


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

# TODO 使用 ExternalProject 方式替代 FetchContent 方式引入
#set(NLOHMANN_JSON_DIR "${CMAKE_CURRENT_BINARY_DIR}/nlohmannjson")
#set(NLOHMANN_JSON_SRC_DIR "${NLOHMANN_JSON_DIR}/src")
#set(NLOHMANN_JSON_BUILD_DIR "${NLOHMANN_JSON_DIR}/build")
#set(NLOHMANN_JSON_OUT_DIR "${NLOHMANN_JSON_DIR}/out")

#ExternalProject_Add(
#    NlohmannJson
#
#    GIT_REPOSITORY git@github.com:nlohmann/json.git
#    GIT_TAG v3.11.2
#
#    SOURCE_DIR "${NLOHMANN_JSON_SRC_DIR}"
#
#    CONFIGURE_COMMAND "${CMAKE_COMMAND}" -S "${NLOHMANN_JSON_SRC_DIR}" -B "${NLOHMANN_JSON_BUILD_DIR}"
#	BUILD_COMMAND "${CMAKE_COMMAND}" "--build" "${NLOHMANN_JSON_BUILD_DIR}" "--config" "${CMAKE_BUILD_TYPE}"
#
#    INSTALL_COMMAND "${CMAKE_COMMAND}" "--install" "${NLOHMANN_JSON_BUILD_DIR}" "--config" "${CMAKE_BUILD_TYPE}" "--prefix" "${NLOHMANN_JSON_OUT_DIR}"
#
#    STEP_TARGETS build
#	EXCLUDE_FROM_ALL TRUE
#)

#message(STATUS "NlohmannJson dir: ${NLOHMANN_JSON_DIR}")
#message(STATUS "NlohmannJson src dir: ${NLOHMANN_JSON_SRC_DIR}")
#message(STATUS "NlohmannJson build dir: ${NLOHMANN_JSON_BUILD_DIR}")
#message(STATUS "NlohmannJson out dir: ${NLOHMANN_JSON_OUT_DIR}")

# 源码拉取一直失败。
#FetchContent_Declare(
#    json
#    GIT_REPOSITORY git@github.com:nlohmann/json.git
#    GIT_TAG v3.11.2
#)
#FetchContent_MakeAvailable(json)


set(JSONCPP_DIR "${CMAKE_CURRENT_BINARY_DIR}/jsoncpp")
set(JSONCPP_SRC_DIR "${JSONCPP_DIR}/src")
set(JSONCPP_BUILD_DIR "${JSONCPP_DIR}/build")
set(JSONCPP_OUT_DIR "${JSONCPP_DIR}/out")

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

project(aliossc)

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

add_subdirectory(aliosst)
add_subdirectory(test1)
