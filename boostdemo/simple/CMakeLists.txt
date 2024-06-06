add_executable(simple)

target_sources(
	simple
	PRIVATE
	"main.cpp"
)

target_link_libraries(
	simple
	PRIVATE
	Boost::asio
)
