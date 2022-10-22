#include "main_panel.h"
#include <cmath>

using namespace cycfi::elements;

main_panel::main_panel() :
	_mouse_over(false),
	_color(0.2, 0.2, 0.2)
{

}

void main_panel::draw(const context& ctx)
{
	ctx.canvas.fill_style(_color);
	ctx.canvas.fill_rect(ctx.bounds);
}

bool main_panel::click(
	const context &ctx,
	mouse_button btn
) {
	if (btn.state == mouse_button::left) {
		_color.blue = std::fmodf(_color.blue + 0.1f, 1.0f);
		// 刷新，示例好像不推荐在数据事件里面刷新。
		//ctx.view.refresh(ctx.bounds);
	}
	return true;
}

/// <summary>
/// 此方法目前没看出作用。
/// </summary>
/// <param name="ctx"></param>
/// <param name="track_info"></param>
void main_panel::keep_tracking(
	const context& ctx,
	tracker_info& track_info
) {
	ctx.view.refresh(ctx.bounds);
}

bool main_panel::cursor(
	context const& ctx, point p,
	cursor_tracking status
) {
	switch (status)
	{
	case cursor_tracking::hovering:
	case cursor_tracking::entering:
		_mouse_over = true;
		// 示例居然在 hovering 刷新，不知道是否会过于频繁。
		ctx.view.refresh(ctx.bounds);
		break;
	case cursor_tracking::leaving:
		_mouse_over = false;
	};
	return false;
}