add_executable(ocv4demo)

target_sources(
    ocv4demo
    PRIVATE
    "src/main.cpp"
)

add_dependencies(
    ocv4demo
    OpenCV
)

# 复制DLL
add_custom_command(
	TARGET ocv4demo
	POST_BUILD
	COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory" "${OPENCV_BIN_DIR}" "${CMAKE_CURRENT_BINARY_DIR}"
)

target_include_directories(
    ocv4demo
    PRIVATE
    "${OPENCV_OUT_DIR}/include"
)

target_link_directories(
    ocv4demo
    PRIVATE
    "${OPENCV_LIB_DIR}"
)

if (MSVC)
    target_link_libraries(
        ocv4demo
        PRIVATE
        "${OPENCV_LIB_CORE}"
        "${OPENCV_LIB_IMGCODECS}"
        "${OPENCV_LIB_IMGPROC}"
        "${OPENCV_LIB_HIGHGUI}"
    )
endif()
