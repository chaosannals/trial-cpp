#include "main_app.h"

using namespace cycfi::elements;

auto constexpr bg_color = rgba(35, 35, 37, 255);
auto background = rbox(bg_color, 5);

main_app::main_app(int argc, char* argv[]) :
	app(argc, argv, "SSH Client", "com.demo.sshclient"),
	_win(name()),
	_view(_win)
{
	auto btn = share(button("a button"));
	btn->on_click = [this](bool) {

	};

	_label = share(label("11111"));
	_win.on_close = [this]() { stop(); };
	_view.content(
		layer(
			vtile(
				hold(_label),
				margin(
					{ 50, 10, 50, 10 },
					hold(btn)
				)
			),
			align_center_middle(
				fixed_size(
					{ 400, 400 },
					link(_main_panel)
				)
			)
		),
		background
	);
}