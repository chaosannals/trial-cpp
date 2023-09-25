#include <iostream>
#include <CLI/CLI.hpp>

int main(int argc, char* argv[]) {
    CLI::App app{ "cli11 demo" };

    std::string host = "127.0.0.1";
    app.add_option("--host", host, "host name.");
    int port = 80;
    app.add_option("-p,--port", port, "port number");

    // -h --help 会直接让程序 exit 不会执行之后的代码。
    CLI11_PARSE(app, argc, argv);

    std::cout << "host: " << host << std::endl
        << "port: " << port << std::endl
        << std::endl;

    return 0;
}
