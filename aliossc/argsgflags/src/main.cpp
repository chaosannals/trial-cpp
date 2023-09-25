#include <iostream>
#include <gflags/gflags.h>

// 而且这个库 Windows 下 必须是  MT(静态链接多线程库) Release （也就是 Debug 是不能链接成功的）

// 参数定义，居然用宏，全局的。
static bool ValidatePort(const char* flagname, gflags::int32 v) {
    return v > 10000 && v < 65535;
}

DEFINE_string(host, "127.0.0.1", "host name.");
DEFINE_int32(port, 80, "port number.");
DEFINE_validator(port, &ValidatePort);

int main(int argc, char *argv[]) {
    // 居然会改到 main 的传参
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    

    std::cin.get();
    return 0;
}
