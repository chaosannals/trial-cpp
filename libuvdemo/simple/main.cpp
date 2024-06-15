#include <iostream>
#include <cstdlib>
#include <uv.h>

int main() {
    uv_loop_t* loop = reinterpret_cast<uv_loop_t*>(std::malloc(sizeof(uv_loop_t)));
    uv_loop_init(loop);

    std::cout << "Now quitting." << std::endl;
    uv_run(loop, UV_RUN_DEFAULT);

    uv_loop_close(loop);
    free(loop);
    std::cin.get();
    return 0;
}
