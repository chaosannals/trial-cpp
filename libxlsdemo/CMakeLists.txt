cmake_minimum_required(VERSION 3.20)

project(libxlsdemo LANGUAGES CXX)

add_executable(libxlsdemo)

target_sources(
	libxlsdemo
	PRIVATE
	"main.cpp"
)

target_link_directories(
	libxlsdemo
	PUBLIC
	"${PROJECT_SOURCE_DIR}"
)

target_link_libraries(
	libxlsdemo
	"libxlsreader.a"
)