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

	// 字体文件定位不到。
	//char const* font_family = u8"文泉驿微米黑, \"WenQuanYi Micro Hei\"";
	//std::string text(u8"asdfdsfdf一千条路");
	char const* font_family = "文泉驿微米黑, \"WenQuanYi Micro Hei\"";
	std::string text("asdfdsfdf一千条路");

	_label = share(label("11111"));
	_win.on_close = [this]() { stop(); };
	_view.content(
		layer(
			vtile(
				hold(_label),
				scroller(
					margin(
						{ 20, 20, 20, 20 },
						align_left_top(
							hsize(800,
								basic_text_box(text, font_descr{ font_family })
							)
						)
					)
				),
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