# 
function(
	CloneAsmJitTo
	SRC_DIR
)
	FetchContent_Declare(
		asmjit
		GIT_REPOSITORY git@github.com:asmjit/asmjit.git
		GIT_TAG master
		SOURCE_DIR "${SRC_DIR}"
	)
	FetchContent_MakeAvailable(asmjit)
endfunction()