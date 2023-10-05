add_executable(funcdemo)

target_sources(
	funcdemo
	PRIVATE
	"src/main.cpp"
)

target_link_libraries(
	funcdemo
	AsmJit::AsmJit
)