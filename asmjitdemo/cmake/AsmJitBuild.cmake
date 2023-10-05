# 
function(
	CloneAsmJitTo
	SRC_DIR
)
	FetchContent_Declare(
		asmjit
		GIT_REPOSITORY git@github.com:asmjit/asmjit.git
		# GIT_REPOSITORY https://gitclone.com/github.com/asmjit/asmjit
		#GIT_TAG master
		GIT_TAG 51b10b19b6631434d3f9ad536a6fb140944a36d2 # 镜像站 gitclone 没有早期的提交，写这个 hash 必须用 github 链接
		SOURCE_DIR "${SRC_DIR}"
	)
	FetchContent_MakeAvailable(asmjit)
endfunction()