#ifndef EXERT_SSHCLIENT_VIEW_MAIN_APP_H
#define EXERT_SSHCLIENT_VIEW_MAIN_APP_H

#include <elements.hpp>
#include "main_panel.h"

class main_app : public cycfi::elements::app {
	using label_ptr = decltype(cycfi::elements::share(cycfi::elements::label("")));

	cycfi::elements::window _win;
	cycfi::elements::view _view;
	label_ptr _label;
	main_panel _main_panel;
public:
	main_app(int argc, char* argv[]);
};

#endif
