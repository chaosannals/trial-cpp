#include <elements.hpp>

using namespace cycfi::elements;

int main(int argc, char* argv[])
{
    app _app(argc, argv, "SSH Client", "com.demo.sshclient");
    window _win(_app.name());
    _win.on_close = [&_app]() { _app.stop(); };
    _app.run();
    return 0;
}