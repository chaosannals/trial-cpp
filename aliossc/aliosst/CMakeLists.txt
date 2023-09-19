add_executable(
	aliosst
)

target_sources(
	aliosst
	PRIVATE
	"src/main.cpp"
)

#if (MSVC)
#	set_target_properties(
#		aliosst
#		PROPERTIES
#		MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
#	)
#endif()

add_dependencies(
	aliosst
	AliYunOssSdk
	# NlohmannJson
	JsonCpp
)

target_include_directories(
	aliosst
	PUBLIC
	"${ALIYUN_OSS_SDK_OUT_DIR}/include"
	"${JSONCPP_OUT_DIR}/include"
)

# 复制 DLL
add_custom_command(
	TARGET aliosst
	POST_BUILD
	COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory" "${ALIYUN_OSS_3P_DLL_DIR}" "${CMAKE_CURRENT_BINARY_DIR}"
	# 使用静态链接可以不用
	COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory" "${JSONCPP_DLL_DIR}" "${CMAKE_CURRENT_BINARY_DIR}"

	# 复制 json
	COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory" "${CMAKE_CURRENT_SOURCE_DIR}/res" "${CMAKE_CURRENT_BINARY_DIR}"
)

target_link_directories(
	aliosst
	PUBLIC
	"${ALIYUN_OSS_SDK_OUT_DIR}/lib"
	"${ALIYUN_OSS_3P_DLL_DIR}" # 阿里太垃圾，这个因为依赖第三方，所以目录名看着是DLL，实则是 DLL 和 LIB 丢一起了。

	"${JSONCPP_OUT_DIR}/lib"
)

target_link_libraries(
	aliosst
	PUBLIC
	alibabacloud-oss-cpp-sdk.lib
	# 以下是 ali oss sdk 依赖的库，还要复制 dll
	libcurl.lib
	libeay32.lib
	ssleay32.lib
	jsoncpp_static.lib
)

# target_link_libraries(aliosst PRIVATE nlohmann_json::nlohmann_json)
