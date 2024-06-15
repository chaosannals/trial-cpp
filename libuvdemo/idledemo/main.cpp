#include <iostream>
#include <uv.h>

int64_t counter = 0;

void wait_for_a_while(uv_idle_t* handle) {
    counter++;

    std::cout << "counter:" << counter << std::endl;

    if (counter >= 10000) {
        uv_idle_stop(handle);
        std::cout << "counter stop." << std::endl;
    }
}

int main() {
    // idle 命名上有点误导, 实则是 event loop 每次循环都会被调用, 应该叫 on_loop_start 或者 on_event_start
    uv_idle_t idler;

    uv_idle_init(uv_default_loop(), &idler);
    // wait_for_a_while 这个方法会被多次调用。
    uv_idle_start(&idler, wait_for_a_while); // 叫 start 也有点误导，实则是注册，叫 add_listener 或者 hook 更恰当

    std::cout << "idling..." << std::endl;
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

    uv_loop_close(uv_default_loop());
    std::cin.get();
    return 0;
}
