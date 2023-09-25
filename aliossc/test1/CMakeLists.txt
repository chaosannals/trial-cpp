add_executable(test1)

target_sources(
	test1
	PRIVATE
	"src/main.cpp"
 )

add_dependencies(
	test1
	Cmdline
)

message(STATUS "cmdline src: ${CMDLINE_SRC_DIR}")

target_include_directories(
	test1
	PUBLIC
	"${CMDLINE_SRC_DIR}"
)


if (MSVC)
	set_target_properties(
		test1
		PROPERTIES
		MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
	)
endif()
