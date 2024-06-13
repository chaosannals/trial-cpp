# include("cmake/SFML.cmake")

add_executable(simple)

target_sources(
    simple
    PRIVATE
    "main.cpp"
)

set_target_properties(
    simple
    PROPERTIES
	MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)

DepSFML(simple)
