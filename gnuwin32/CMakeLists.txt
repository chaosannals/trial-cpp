cmake_minimum_required(VERSION 3.24)

include("cmake/GnuWin32Bison.cmake")
include("cmake/GnuWin32Flex.cmake")

GnuWin32_DownloadFlex()
GnuWin32_DownloadBison()

project(gnuwin32demo)

add_subdirectory(calcul)
add_subdirectory(woco)
add_subdirectory(wocopp)
