add_executable(argsgflags)

target_sources(
    argsgflags
    PRIVATE
    "src/main.cpp"
)

target_link_libraries(
    argsgflags
    gflags::gflags
)

if (MSVC)
	set_target_properties(
		argsgflags
		PROPERTIES
		MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
	)
endif()
