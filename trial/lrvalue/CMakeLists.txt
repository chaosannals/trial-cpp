cmake_minimum_required(VERSION 3.15.0)
project(trial LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)


add_executable(lrvalue)

target_sources(
	lrvalue
	PRIVATE
	"./main.cpp"
)