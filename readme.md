# [trial-cpp](https://github.com/chaosannals/trial-cpp)

## CMake

由于历史原因 c/c++ 的项目是没有统一的包管理，甚至没有统一个构建流程。

## 替代 makefile 的命令

[官方文档](https://cmake.org/cmake/help/latest/command/add_custom_command.html#examples-generating-files)

```cmake
# 这个命令这种写法可以提到 makefile 的模式
# 1.目标结果 OUTPUT  2.依赖文件 DEPENDS  3.执行命令 COMMAND
# 所以可以替代 makefile
add_custom_command(
  OUTPUT "out-$<CONFIG>.c"
  COMMAND someTool -i ${CMAKE_CURRENT_SOURCE_DIR}/in.txt
                   -o "out-$<CONFIG>.c"
                   -c "$<CONFIG>"
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/in.txt
  VERBATIM)
```

### ExternalProject 和 FetchContent 

如果要引入的库是自己定义的流程，选用 ExternalProject 编译获取生成物，再通过配置头文件导入，二进制链接路径等配置，引入。

如果此项目的 cmake 脚本按照 cmake 的规范写的，此时可以通过 FetchContent 引入为一个项目。

注：并非所有有 CmakeLists.txt 的项目都可以用 FetchContent ,而是此项目的作者有按照 FetchContent 的规范去写 CMake 脚本。因为 CMake 本身是一个脚本，你不按规范来也是可以的，而且 FetchContent 还是后加入的东西，更是不能做强制规范。
