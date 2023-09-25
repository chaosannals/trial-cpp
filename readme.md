# [trial-cpp](https://github.com/chaosannals/trial-cpp)

## CMake

由于历史原因 c/c++ 的项目是没有统一的包管理，甚至没有统一个构建流程。
### ExternalProject 和 FetchContent 

如果要引入的库是自己定义的流程，选用 ExternalProject 编译获取生成物，再通过配置头文件导入，二进制链接路径等配置，引入。

如果此项目的 cmake 脚本按照 cmake 的规范写的，此时可以通过 FetchContent 引入为一个项目。

注：并非所有有 CmakeLists.txt 的项目都可以用 FetchContent ,而是此项目的作者有按照 FetchContent 的规范去写 CMake 脚本。因为 CMake 本身是一个脚本，你不按规范来也是可以的，而且 FetchContent 还是后加入的东西，更是不能做强制规范。
