include(FetchContent)

function(FetchSFML)
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY git@github.com:SFML/SFML.git
        GIT_TAG 2.6.x
        GIT_SHALLOW ON # 浅克隆，git 参数加 --depth=1
        GIT_PROGRESS ON # 打印下载进度
    )
    FetchContent_MakeAvailable(SFML)
    message(STATUS "[SFML] ${SFML_SOURCE_DIR}")
endfunction()


function(
    DepSFML
    TARGET_NAME
)
    target_link_libraries("${TARGET_NAME}" PRIVATE sfml-graphics)
    target_compile_features("${TARGET_NAME}" PRIVATE cxx_std_17)

    if(WIN32)
        add_custom_command(
            TARGET "${TARGET_NAME}"
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${TARGET_NAME}>
            VERBATIM)
    endif()
endfunction()
