# 这个库只兼容 Linux GCC ，如果 Windows 要使用，要修改源码，这样很丑陋。
# 虽然修改源码也就几行，如下两处：
#1.第一处
##ifdef __GNUC__
##include <cxxabi.h>
##endif
#
#2.第二处
#static inline std::string demangle(const std::string &name)
#{
##ifdef _MSC_VER
#  return name;
## elif defined(__GNUC__)
#  int status=0;
#  char *p=abi::__cxa_demangle(name.c_str(), 0, 0, &status);
#  std::string ret(p);
#  free(p);
#  return ret;
##else
##error unexpected c compiler
##endif
#}

function(
    ImportCmdline
)
    set(CMDLINE_SRC_DIR "${CMAKE_BINARY_DIR}/cmdline")
    set(CMDLINE_SRC_DIR "${CMDLINE_SRC_DIR}" PARENT_SCOPE)
    message(STATUS "cmdline dir: ${CMDLINE_SRC_DIR}")

    ExternalProject_Add(
        Cmdline
        GIT_REPOSITORY "git@github.com:tanakh/cmdline.git"

        SOURCE_DIR "${CMDLINE_SRC_DIR}"

        CONFIGURE_COMMAND ""
	    BUILD_COMMAND ""

        INSTALL_COMMAND ""

        STEP_TARGETS download
	    EXCLUDE_FROM_ALL FALSE
    )
endfunction()
