# 官网的引入方式比较丑陋，是通过手动 git 拉取源码，配置好构造变量后再 include 一个 cmake 脚本。
# 这个流程里需要提供一个 APP_DIR 使得项目只能一个，同时这种使用 cmake 的方式也不常规。
# 以下使用 cmake 的去拉取而不是手动 git ，此方式在 wxwidgets 下使用过可行。


function(
    ImportBlend2D
)
    # 函数内作用域变量
	set(BLEND2D_DIR "${CMAKE_BINARY_DIR}/blend2d")
    set(BLEND2D_SRC_DIR "${BLEND2D_DIR}/blend2d") # 目录名必须是 blend2d
    set(BLEND2D_BUILD_DIR "${BLEND2D_DIR}/build")
    set(BLEND2D_OUT_DIR "${BLEND2D_DIR}/out")
    set(BLEND2D_ASMJIT_SRC_DIR "${BLEND2D_DIR}/asmjit") # 目录必须放在 blend2d 源码同级

    set(BLEND2D_OUT_DIR "${BLEND2D_DIR}/out" PARENT_SCOPE)
    #set(BLEND2D_STATIC TRUE)
    message(STATUS "blend2d dir: ${BLEND2D_DIR}")

    # 依赖的 AsmJit 只拉取源码，目录必须和 blend2d 同级且目录名叫 asmjit 
	ExternalProject_Add(
		asmjit
		GIT_REPOSITORY    git@github.com:asmjit/asmjit.git
		GIT_TAG           master
		SOURCE_DIR "${BLEND2D_ASMJIT_SRC_DIR}"

		# 不配置
		CONFIGURE_COMMAND ""
		# 不构建
		BUILD_COMMAND ""
		# 不安装
		INSTALL_COMMAND ""

		# 配置 build 阶段就生成目标并安装
		STEP_TARGETS build
		EXCLUDE_FROM_ALL TRUE
	)

    # Blend2D
    ExternalProject_Add(
        blend2d

        GIT_REPOSITORY git@github.com:blend2d/blend2d.git
        GIT_TAG master
    
        SOURCE_DIR "${BLEND2D_SRC_DIR}"

        # 可以在这里通过 -D 设置参数
        # 静态设置 -DBLEND2D_EMBED=TRUE -DBLEND2D_STATIC=TRUE 不知道为什么会少了几个函数的定义
        CONFIGURE_COMMAND "${CMAKE_COMMAND}" -S "${BLEND2D_SRC_DIR}" -B "${BLEND2D_BUILD_DIR}"
	    
        BUILD_COMMAND "${CMAKE_COMMAND}" "--build" "${BLEND2D_BUILD_DIR}" "--config" "${CMAKE_BUILD_TYPE}"

        # 执行安装 ${CMAKE_MAKE_PROGRAM} 是 ninja 、 make 、nmake 之流。
        INSTALL_COMMAND "${CMAKE_COMMAND}" "--install" "${BLEND2D_BUILD_DIR}" "--config" "${CMAKE_BUILD_TYPE}" "--prefix" "${BLEND2D_OUT_DIR}"

        # 配置 build 阶段就生成目标并安装
	    STEP_TARGETS build
	    EXCLUDE_FROM_ALL TRUE
    )

    add_dependencies(blend2d asmjit)
endfunction()
