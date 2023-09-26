add_executable(calcul)

target_sources(
    calcul
    PRIVATE
    "src/main.cpp"
)

add_dependencies(
    calcul
    flex
    bison
)
