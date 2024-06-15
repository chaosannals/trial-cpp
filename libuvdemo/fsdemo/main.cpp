#include<iostream>
#include <uv.h>

// 回调地狱，这库,还一堆全局。
uv_fs_t open_req;
uv_fs_t close_req;
uv_fs_t read_req;
uv_fs_t write_buf_req;
uv_loop_t* loop;

char buffer[512];
uv_buf_t iov;

void on_close(uv_fs_t* req) {
    std::cout << "close." << std::endl;
}

void on_write_buf(uv_fs_t* req) {
    std::cout << "write buf." << std::endl;
}

void on_read(uv_fs_t* req) {
    std::cout << "on_read" << std::endl;
    if (req->result < 0) {
        std::cout << "read filed." << std::endl;
    }
    else if (req->result == 0) {
        uv_fs_close(loop, &close_req, open_req.result, on_close);
    }
    else {
        // uv_file 这个估计是 fd
        uv_fs_write(loop, &write_buf_req, 0, &iov, 1, -1, on_write_buf);
        // uv_fs_write(loop, &write_buf_req, 1, &iov, 1, -1, on_write_buf);
    }
}

void on_open(uv_fs_t* req) {
    std::cout << "cb lay:" << req->result << std::endl;
    if (req->result >= 0) {
        iov = uv_buf_init(buffer, sizeof(buffer));
        uv_fs_read(loop, &read_req, req->result, &iov, 1, -1, on_read);
        std::cout << "read out lay:" << read_req.result << std::endl;
    }
}

int main() {
    loop = reinterpret_cast<uv_loop_t*>(std::malloc(sizeof(uv_loop_t)));
    uv_loop_init(loop);

    auto path = "fsdemo.txt";

    int fd = uv_fs_open(loop, &open_req, path, O_CREAT | O_RDWR, 0644, on_open);
    std::cout << "out lay:" << open_req.result << " fd: " << std::endl;

    uv_run(loop, UV_RUN_DEFAULT);

    uv_loop_close(loop);
    free(loop);
    std::cin.get();
    return 0;
}
