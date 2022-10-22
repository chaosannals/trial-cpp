cmake_minimum_required(VERSION 3.14)

project(cmdemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED 17)

set(CMDEMO_LIBS_DIR "${PROJECT_SOURCE_DIR}/libs")
set(CMDEMO_LIBSSH2_DIR "${CMDEMO_LIBS_DIR}/libssh2")
set(CMDEMO_LIBSSH2_INC_DIR "${CMDEMO_LIBSSH2_DIR}/include")
set(CMDEMO_LIBSSH2_OUT_DIR "${PROJECT_BINARY_DIR}/libs/libssh2/src/${CMAKE_CONFIGURATION_TYPES}")

# 不加配置的话，windows 会使用系统自带的 bcrypt.h  WinCNG，这个会出现一些兼容问题。
# 使用 OpenSSL 的问题最少，但是安装比较麻烦。
add_subdirectory("libs/libssh2")
add_subdirectory(ssh2demo)
add_subdirectory(ocvdemo)
