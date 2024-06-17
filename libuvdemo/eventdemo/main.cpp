#include <iostream>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <uv.h>

void run_command(uv_fs_event_t* handle, const char *filename, int events, int status) {
    char path[1024];
    size_t size = 1023;
    uv_fs_event_getpath(handle, path, &size);
    path[size] = '\0';

    std::fprintf(stderr, "change detected in %s", path);
    if (events & UV_RENAME) {
        std::fprintf(stderr, "renamed");
    }
    if (events & UV_CHANGE) {
        std::fprintf(stderr, "changed");
    }
    std::fprintf(stderr, " %s\n", filename ? filename : "[null]");
    // system(command);
}

int main() {
    uv_loop_t* loop = uv_default_loop();

    auto dir = std::filesystem::current_path().string();

    std::cout << "here:" << dir << std::endl;

    //uv_fs_event_t* event_req = std::malloc(sizeof(uv_fs_event_t));
    uv_fs_event_t* event_req = new uv_fs_event_t;
    uv_fs_event_init(loop, event_req);
    uv_fs_event_start(event_req, run_command, dir.c_str(), UV_FS_EVENT_RECURSIVE);

    uv_run(loop, UV_RUN_DEFAULT);
    uv_loop_close(loop);

    std::cin.get();
    return 0;
}
