add_executable(asmjit_simple)

add_dependencies(asmjit_simple AsmJit::AsmJit)

FetchContent_GetProperties(
	asmjit
	SOURCE_DIR ASMJIT_SOURCE_DIR
	BINARY_DIR ASMJIT_BINARY_DIR
   POPULATED ASMJIT_POPULATED
)

message(STATUS "asmjit src dir: ${ASMJIT_SOURCE_DIR} bin dir: ${ASMJIT_BINARY_DIR} populated: ${ASMJIT_POPULATED}")

# FetchContent 直接引入，无须指定  include directories link_directories 但是需要复制 dll 用于调试（如果有的话）。
target_link_libraries(asmjit_simple AsmJit::AsmJit)

## 以下需要配置和复制

#target_include_directories(
#	asmjit_simple
#	PRIVATE
#	"${ASMJIT_SOURCE_DIR}/src"
#)

#target_link_directories(
#	asmjit_simple
#	PRIVATE
#	${ASMJIT_BINARY_DIR}
#)

#target_link_libraries(
#	asmjit_simple
#	PRIVATE
#	"asmjit"
#)


## 复制 dll 到目录下，启用了静态所以不用复制，动态的话需要复制

#get_target_property(
#	TARGET_BINARY_DIR
#	asmjit_simple
#	BINARY_DIR
#)

#add_custom_command(
#	TARGET asmjit_simple
#	POST_BUILD
#	COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory" "${ASMJIT_BINARY_DIR}" "${TARGET_BINARY_DIR}"
#)
#message(STATUS "copy asmjit: ${ASMJIT_BINARY_DIR} => ${TARGET_BINARY_DIR}")

target_sources(
	asmjit_simple
	PRIVATE
	"src/main.cpp"
)