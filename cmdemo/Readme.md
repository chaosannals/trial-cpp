# cmake demo

## 库及依赖

### openssl 

OpenSSL 没有写 Cmake 的支持脚本，Windows 下需要以下工具进行编译。

- perl (windows 下发行版比较多，这里选用 [strawberryperl](https://strawberryperl.com/)
- [NASM](https://www.nasm.us/)
- Vc++ 编译器。

克隆 OpenSSL 源码，启动 VC++ 编译命令行环境 切换到源码目录下，根据生成的目标使用一下命令配置。

```bash
# 32bit
perl Configure VC-WIN32

# 64bit
perl Configure VC-WIN64A 

# Arm (win-arm64) OpenSSL
perl Configure VC-WIN64-ARM

# 指定平台
perl Configure [to let Configure figure out the platform]

# 指定安装目录
perl Configure VC-WIN64A --prefix="D:\OpenSSL" --openssldir="D:\SSL"
```

如果不配置，默认的 nmake install 会把程序安装到以下：

```
For VC-WIN32, the following defaults are use:

PREFIX:      %ProgramFiles(x86)%\OpenSSL
OPENSSLDIR:  %CommonProgramFiles(x86)%\SSL

For VC-WIN64, the following defaults are use:

PREFIX:      %ProgramW6432%\OpenSSL
OPENSSLDIR:  %CommonProgramW6432%\SSL

Should those environment variables not exist (on a pure Win32 installation for examples), these fallbacks are used:

PREFIX:      %ProgramFiles%\OpenSSL
OPENSSLDIR:  %CommonProgramFiles%\SSL
```

```bash
# 构建
nmake

# 安装
namke install
```
