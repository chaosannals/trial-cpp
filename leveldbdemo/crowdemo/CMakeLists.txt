add_executable(crowdemo)

target_sources(
    crowdemo
    PRIVATE
    "main.cpp"
)

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
