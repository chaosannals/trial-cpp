add_executable(asmjit_simple)

add_dependencies(asmjit_simple AsmJit::AsmJit)

FetchContent_GetProperties(
	asmjit
	SOURCE_DIR ASMJIT_SOURCE_DIR
	BINARY_DIR ASMJIT_BINARY_DIR
	POPULATED ASMJIT_POPULATED
)

message(STATUS "asmjit src dir: ${ASMJIT_SOURCE_DIR} bin dir: ${ASMJIT_BINARY_DIR} populated: ${ASMJIT_POPULATED}")

target_include_directories(
	asmjit_simple
	PRIVATE
	"${ASMJIT_SOURCE_DIR}/src"
)

target_link_directories(
	asmjit_simple
	PRIVATE
	${ASMJIT_BINARY_DIR}
)

target_link_libraries(
	asmjit_simple
	PRIVATE
	"asmjit"
)

get_target_property(
	TARGET_BINARY_DIR
	asmjit_simple
	BINARY_DIR
)

add_custom_command(
	TARGET asmjit_simple
	POST_BUILD
	COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory" "${ASMJIT_BINARY_DIR}" "${TARGET_BINARY_DIR}"
)
message(STATUS "copy asmjit: ${ASMJIT_BINARY_DIR} => ${TARGET_BINARY_DIR}")

target_sources(
	asmjit_simple
	PRIVATE
	"src/main.cpp"
)