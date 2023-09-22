cmake_minimum_required(VERSION 3.24)

include(ExternalProject)

# 通过 .editorconfig 设置源码字符集为 UTF-8
# TODO 一些微软员工的博文经常看到说 VS 如果UTF-8不使用BOM 会有奇怪的 BUG。
# 观察是否会因为没有 BOM 导致问题。

set(OPENCV_DIR "${CMAKE_CURRENT_BINARY_DIR}/opencv")
set(OPENCV_SRC_DIR "${OPENCV_DIR}/src")
set(OPENCV_BUILD_DIR "${OPENCV_DIR}/build")
set(OPENCV_OUT_DIR "${OPENCV_DIR}/out")

message(STATUS "OpenCV dir: ${OPENCV_DIR}")
message(STATUS "OpenCV src dir: ${OPENCV_SRC_DIR}")
message(STATUS "OpenCV build dir: ${OPENCV_BUILD_DIR}")
message(STATUS "OpenCV out dir: ${OPENCV_OUT_DIR}")

ExternalProject_Add(
    OpenCV

    # github 有墙，使用镜像链接。
    GIT_REPOSITORY "https://gitclone.com/github.com/opencv/opencv" 
    # GIT_REPOSITORY "git@github.com:opencv/opencv.git"
    GIT_TAG 4.8.0

    SOURCE_DIR "${OPENCV_SRC_DIR}"

    CONFIGURE_COMMAND "${CMAKE_COMMAND}" -S "${OPENCV_SRC_DIR}" -B "${OPENCV_BUILD_DIR}" -DBUILD_JAVA=OFF
	BUILD_COMMAND "${CMAKE_COMMAND}" "--build" "${OPENCV_BUILD_DIR}" "--config" "${CMAKE_BUILD_TYPE}"

    INSTALL_COMMAND "${CMAKE_COMMAND}" "--install" "${OPENCV_BUILD_DIR}" "--config" "${CMAKE_BUILD_TYPE}" "--prefix" "${OPENCV_OUT_DIR}"

    STEP_TARGETS build
	EXCLUDE_FROM_ALL TRUE
)

project(vscmdemo)

# 必须在 project 之后才有 MSVC
if(MSVC)
    if (CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
        set(OPENCV_LIB_CORE "opencv_core480d.lib")
        set(OPENCV_LIB_IMGCODECS "opencv_imgcodecs480d.lib")
        set(OPENCV_LIB_IMGPROC "opencv_imgproc480d.lib")
        set(OPENCV_LIB_HIGHGUI "opencv_highgui480d.lib")
    else()
        set(OPENCV_LIB_CORE "opencv_core480.lib")
        set(OPENCV_LIB_IMGCODECS "opencv_imgcodecs480.lib")
        set(OPENCV_LIB_IMGPROC "opencv_imgproc480.lib")
        set(OPENCV_LIB_HIGHGUI "opencv_highgui480.lib")
    endif()
    message(STATUS "opencv core: ${OPENCV_LIB_CORE}") # 核心库
    message(STATUS "opencv imgcodecs: ${OPENCV_LIB_IMGCODECS}") # 解码编码图片 png jpg  imread imwrite 格式相关
    message(STATUS "opencv imgproc: ${OPENCV_LIB_IMGPROC}") # 图片处理 cvtColor 等处理图片的函数
    message(STATUS "opencv highgui: ${OPENCV_LIB_HIGHGUI}") # GUI 用于查看结果相关的函数 imshow

    message(STATUS "msvc version: ${MSVC_VERSION}")
    if (MSVC_VERSION EQUAL 1400)
        set(OPENCV_VC_VERSION vc8)
    elseif (MSVC_VERSION EQUAL 1500)
        set(OPENCV_VC_VERSION vc9)
    elseif (MSVC_VERSION EQUAL 1600)
        set(OPENCV_VC_VERSION vc10)
    elseif (MSVC_VERSION EQUAL 1700)
        set(OPENCV_VC_VERSION vc11)
    elseif (MSVC_VERSION EQUAL 1800)
        set(OPENCV_VC_VERSION vc12)
    elseif (MSVC_VERSION EQUAL 1900)
        set(OPENCV_VC_VERSION vc14)
    elseif (MSVC_VERSION EQUAL 1937)
        set(OPENCV_VC_VERSION vc17)
    endif()
    if (CMAKE_CL_64)
        set(OPENCV_BIN_DIR "${OPENCV_OUT_DIR}/x64/${OPENCV_VC_VERSION}/bin")
        set(OPENCV_LIB_DIR "${OPENCV_OUT_DIR}/x64/${OPENCV_VC_VERSION}/lib")
    else()
        set(OPENCV_BIN_DIR "${OPENCV_OUT_DIR}/${OPENCV_VC_VERSION}/bin")
        set(OPENCV_LIB_DIR "${OPENCV_OUT_DIR}/${OPENCV_VC_VERSION}/lib")
    endif()

    message(STATUS "openvc dll dir: ${OPENCV_BIN_DIR}")
    message(STATUS "openvc lib dir: ${OPENCV_LIB_DIR}")
    
endif()

add_subdirectory(ocv4demo)

