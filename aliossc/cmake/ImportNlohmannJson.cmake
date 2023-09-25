function(
    ImportNlohmannJson
)
    message(STATUS "NlohmannJson useless .")
    # TODO 使用 ExternalProject 方式替代 FetchContent 方式引入
    #set(NLOHMANN_JSON_DIR "${CMAKE_CURRENT_BINARY_DIR}/nlohmannjson")
    #set(NLOHMANN_JSON_SRC_DIR "${NLOHMANN_JSON_DIR}/src")
    #set(NLOHMANN_JSON_BUILD_DIR "${NLOHMANN_JSON_DIR}/build")
    #set(NLOHMANN_JSON_OUT_DIR "${NLOHMANN_JSON_DIR}/out")

    #ExternalProject_Add(
    #    NlohmannJson
    #
    #    GIT_REPOSITORY git@github.com:nlohmann/json.git
    #    GIT_TAG v3.11.2
    #
    #    SOURCE_DIR "${NLOHMANN_JSON_SRC_DIR}"
    #
    #    CONFIGURE_COMMAND "${CMAKE_COMMAND}" -S "${NLOHMANN_JSON_SRC_DIR}" -B "${NLOHMANN_JSON_BUILD_DIR}"
    #	BUILD_COMMAND "${CMAKE_COMMAND}" "--build" "${NLOHMANN_JSON_BUILD_DIR}" "--config" "${CMAKE_BUILD_TYPE}"
    #
    #    INSTALL_COMMAND "${CMAKE_COMMAND}" "--install" "${NLOHMANN_JSON_BUILD_DIR}" "--config" "${CMAKE_BUILD_TYPE}" "--prefix" "${NLOHMANN_JSON_OUT_DIR}"
    #
    #    STEP_TARGETS build
    #	EXCLUDE_FROM_ALL TRUE
    #)

    #message(STATUS "NlohmannJson dir: ${NLOHMANN_JSON_DIR}")
    #message(STATUS "NlohmannJson src dir: ${NLOHMANN_JSON_SRC_DIR}")
    #message(STATUS "NlohmannJson build dir: ${NLOHMANN_JSON_BUILD_DIR}")
    #message(STATUS "NlohmannJson out dir: ${NLOHMANN_JSON_OUT_DIR}")

    # 源码拉取一直失败。
    #FetchContent_Declare(
    #    json
    #    GIT_REPOSITORY git@github.com:nlohmann/json.git
    #    GIT_TAG v3.11.2
    #)
    #FetchContent_MakeAvailable(json)
endfunction()
