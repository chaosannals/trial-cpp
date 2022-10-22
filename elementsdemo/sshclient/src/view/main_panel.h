#ifndef EXERT_SSHCLIENT_VIEW_MAIN_WINDOW_H
#define EXERT_SSHCLIENT_VIEW_MAIN_WINDOW_H

#include <elements.hpp>
#include <infra/support.hpp>


class main_panel :
	public cycfi::elements::tracker<>
{
	bool _mouse_over;
	cycfi::elements::color _color;
public:
	main_panel();

	// 元素绘制重写
	void draw(const cycfi::elements::context &ctx) override;
	bool click(const cycfi::elements::context &ctx, cycfi::elements::mouse_button btn) override;
	void keep_tracking(const cycfi::elements::context &ctx, cycfi::elements::tracker_info& track_info) override;
	bool cursor(const cycfi::elements::context &ctx, cycfi::elements::point p, cycfi::elements::cursor_tracking status);
};

#endif
