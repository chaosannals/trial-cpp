#ifndef EXERT_SSHCLIENT_VIEW_MAIN_APP_H
#define EXERT_SSHCLIENT_VIEW_MAIN_APP_H

#include <elements.hpp>

class main_app : public cycfi::elements::app {
	cycfi::elements::window _win;
public:
	main_app(int argc, char* argv[]);
};

#endif
