#include <slintdemo_ui.h>
#ifdef WIN32
#include <Windows.h>
#endif

int main(int argc, char** argv)
{
#ifdef WIN32
    FreeConsole();
#endif
    auto hello_world = HelloWorld::create();
    hello_world->set_my_page(1);
    hello_world->set_my_label("Hello from C++");
    
    hello_world->run();
    return 0;
}