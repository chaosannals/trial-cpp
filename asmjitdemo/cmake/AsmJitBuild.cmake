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
		GIT_TAG 51b10b19b6631434d3f9ad536a6fb140944a36d2 # ����վ gitclone û�����ڵ��ύ��д��� hash ������ github ����
		SOURCE_DIR "${SRC_DIR}"
	)
	FetchContent_MakeAvailable(asmjit)
endfunction()