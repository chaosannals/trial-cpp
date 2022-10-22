# exert elements

```bash
# 克隆项目并初始化子模块，一般用于构建静态库。
git clone --recurse-submodules  https://github.com/cycfi/elements.git
```

```bash
# 新建项目时，引入子模块 elements 及其依赖。
git submodule add https://github.com/cycfi/elements.git

git submodule init
git submodule update --init --recursive
```


.gitmodules 加入： ignore = dirty  忽略改动

```ini
[submodule "sshclient/lib/elements"]
	path = sshclient/lib/elements
	url = https://github.com/cycfi/elements.git
	ignore = dirty
```


## 附录

### windows

windows 下构建 把 ninja 改成  vs 。

如果使用 ninja 生成，需要一堆 linux 迁移到 windows 下的依赖工具。

[gnome 下载 win32 ](https://download.gnome.org/binaries/win32/dependencies/)
[gnome 下载 win64 ](https://download.gnome.org/binaries/win64/dependencies/)

注：Could NOT find PkgConfig (missing: PKG_CONFIG_EXECUTABLE)
下载 pkg-config 