add_executable(oatppdemo)

target_sources(
    oatppdemo
    PRIVATE
    "main.cpp"
)

target_link_libraries(
    oatppdemo
    PUBLIC
    oatpp
)
