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