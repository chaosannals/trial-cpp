add_executable(sml2demo)

target_sources(
    sml2demo
    PRIVATE
    "main.cpp"
)

target_include_directories(
    sml2demo
    PRIVATE
    "${BOOST_EXT_SML2_SRC_DIR}"
)
