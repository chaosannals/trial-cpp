add_executable(ssh2demo)

target_sources(
	ssh2demo
	PRIVATE
	main.cpp
)

target_include_directories(
	ssh2demo
	PRIVATE 
	${CMDEMO_LIBSSH2_INC_DIR}
)

target_link_directories(
	ssh2demo
	PRIVATE
	${CMDEMO_LIBSSH2_OUT_DIR}
)

target_link_libraries(
	ssh2demo
	PRIVATE
	libssh2
)