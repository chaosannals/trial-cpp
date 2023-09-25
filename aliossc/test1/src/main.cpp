#include <iostream>
#include <cmdline.h>


/* Windows 下运行代码需要修改 cmdline.h 源码 详见 cmake ImportCmdline.cmake */
int main(int argc, char *argv[]) {
    cmdline::parser parser;

    parser.add<std::string>("host", 'h', "host name.", true, "127.0.0.1");
    parser.add<int>("port", 'p', "port number", false, 80, cmdline::range(10000, 65535));

    parser.parse(argc, argv);

    std::cout << "host: " << parser.get<std::string>("host") << std::endl
        << "port: " << parser.get<int>("port") << std::endl
        << std::endl;

	std::cin.get();

	return 0;
}
