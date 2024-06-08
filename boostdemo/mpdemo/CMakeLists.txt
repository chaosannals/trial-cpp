add_executable(mpdemo)

target_sources(
    mpdemo
    PRIVATE
    "main.cpp"
)

target_include_directories(
    mpdemo
    PRIVATE
    "${BOOST_EXT_MP_SRC_DIR}"
)
