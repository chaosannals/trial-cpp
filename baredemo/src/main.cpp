#include <memory>
#include <elements.hpp>
#include <matoya.h>
#include <bcrypt.h>

using namespace cycfi::elements;

auto constexpr bkd_color = rgba(35, 35, 37, 255);
auto background = box(bkd_color);

auto make_child_window(rect bounds, char const* title)
{
    return closable_child_window(
        title,
        bounds,
        scroller(image{ "deep_space.jpg" })
    );
}

int main(int argc, char* argv[])
{
    app _app(argc, argv, "Child Window", "com.cycfi.child-window");
    window _win(_app.name());
    _win.on_close = [&_app]() { _app.stop(); };

    view view_(_win);

    char a[] = "1111232323";
    auto b = std::unique_ptr<char[]>(new char[1024]);
    MTY_BytesToBase64(a, sizeof(a), b.get(), 1024);

    auto cw1 = make_child_window({ 10, 10, 300, 200 }, b.get());
    

    view_.content(
        cw1,
        make_child_window({ 60, 60, 350, 250 }, "Child Window 2"),
        background
    );

    _app.run();
    return 0;
}