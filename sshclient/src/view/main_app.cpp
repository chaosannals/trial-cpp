#include "main_app.h"

main_app::main_app(int argc, char* argv[]) :
	app(argc, argv, "SSH Client", "com.demo.sshclient"),
	_win(name())
{
	_win.on_close = [this]() { stop(); };
}