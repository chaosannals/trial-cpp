add_executable(test1)

target_sources(
	test1
	PRIVATE
	"src/main.cpp"
)

if (MSVC)
	set_target_properties(
		test1
		PROPERTIES
		MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
	)
endif()