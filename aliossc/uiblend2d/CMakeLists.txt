add_executable(uiblend2d)

target_sources(
    uiblend2d
    PRIVATE
    "src/main.cpp"
)

add_dependencies(
    uiblend2d
    blend2d
)

target_include_directories(
    uiblend2d
    PRIVATE
    "${BLEND2D_OUT_DIR}/include"
)

target_link_directories(
    uiblend2d
    PRIVATE
    "${BLEND2D_OUT_DIR}/lib"
)

if (MSVC)
    set_target_properties(
		uiblend2d
		PROPERTIES
		MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
	)
    target_link_libraries(
        uiblend2d
        PRIVATE
        blend2d.lib
    )

    # 复制 DLL
    add_custom_command(
	    TARGET uiblend2d
	    POST_BUILD
	    COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory" "${BLEND2D_OUT_DIR}/bin" "${CMAKE_CURRENT_BINARY_DIR}"
    )
endif()
