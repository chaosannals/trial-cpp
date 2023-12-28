# libxls demo

如果拉去的源码 git 仓库的需要执行 ./bootstrap 生成 configure
下载 zip 的不需要，已经有 configure 了。

这个库不能处理图片。

Windows 版本在 Msys2 下没编译过。

```bash
# 安装工具库
pacman -S gcc make
pacman -S mingw-w64-x86_64-libiconv mingw-w64-x86_64-iconv
pacman -S automake
pacman -S autoconf

# 有个环境变量配置但是高版本 Msys2 反而会导致 gcc 不识别参数
# 所以没用
CC='gcc -mno-cygwin'

# 配置和编译
./configure --host=mingw32 --build=mingw32 --with-iconv=no --prefix=/e/libxls
make
make install
```


Linux 在 WSL Ubuntu-22.04 编译，但是只有 .so 文件，然后找到 *.o 的目录手动生成的静态库。

CMake 文件只是写给 Linux 没给 Windows 做适配。

```bash
# 配置并编译
./configure --prefix=/mnt/e/libxls
make
make install

# 生成静态库
ar crv libxlsreader.a *.o
```

## 报错和处理

> AX_CXX_COMPILE_STDCXX_11 macro not found

```bash
sudo apt install autoconf-archive
```


> macro 'AM_ICONV' not found in library

```bash
apt install -y gettext
```

