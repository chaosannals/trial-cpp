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

# ���� DLL
add_custom_command(
	TARGET aliosst
	POST_BUILD
	COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory" "${ALIYUN_OSS_3P_DLL_DIR}" "${CMAKE_CURRENT_BINARY_DIR}"
	# ʹ�þ�̬���ӿ��Բ���
	COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory" "${JSONCPP_DLL_DIR}" "${CMAKE_CURRENT_BINARY_DIR}"

	# ���� json
	COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory" "${CMAKE_CURRENT_SOURCE_DIR}/res" "${CMAKE_CURRENT_BINARY_DIR}"
)

target_link_directories(
	aliosst
	PUBLIC
	"${ALIYUN_OSS_SDK_OUT_DIR}/lib"
	"${ALIYUN_OSS_3P_DLL_DIR}" # ����̫�����������Ϊ����������������Ŀ¼��������DLL��ʵ���� DLL �� LIB ��һ���ˡ�

	"${JSONCPP_OUT_DIR}/lib"
)

target_link_libraries(
	aliosst
	PUBLIC
	alibabacloud-oss-cpp-sdk.lib
	# ������ ali oss sdk �����Ŀ⣬��Ҫ���� dll
	libcurl.lib
	libeay32.lib
	ssleay32.lib
	jsoncpp_static.lib
)

# target_link_libraries(aliosst PRIVATE nlohmann_json::nlohmann_json)