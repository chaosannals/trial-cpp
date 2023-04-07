#include "slintdemo_ui.h"
#ifdef WIN32
#include <Windows.h>
#endif

int main(int argc, char** argv)
{
#ifdef WIN32
    FreeConsole();
#endif
    auto hello_world = HelloWorld::create();
    hello_world->set_my_label("Hello from C++");
    // Show the window and spin the event loop until the window is closed.
    hello_world->run();
    return 0;
}