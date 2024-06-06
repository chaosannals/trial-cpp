add_executable(crowdemo)

target_sources(
	crowdemo
	PRIVATE
	"main.cpp"
)


# 按正常使用 boost 需要启动这个宏
# Crow 没有规范使用 asio ，asio.hpp 是一堆 #include <boost/asio/*> ，而 Crow 是从 #include<asio/*> 。需要重复引入 asio 的 include 路径。
# 加入这个宏后变成 boost 模式引入。
target_compile_definitions(
    crowdemo
    PRIVATE
    "-DCROW_USE_BOOST"
)

target_link_libraries(
	crowdemo
	PRIVATE
	Boost::asio
	Crow
)
