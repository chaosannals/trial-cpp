#include <iostream>
#include <uv.h>

uv_loop_t* loop;
uv_write_t write_req;

void on_close(uv_handle_t* handle) {
    std::cout << "on_close" << std::endl;
}

void on_write(uv_write_t* req, int status) {
    std::cout << "on_write" << std::endl;
}

template<int size>
void write_uv(uv_write_t* req, uv_stream_t* handle, const char (&buf)[size]) {
    uv_buf_t out = uv_buf_init(reinterpret_cast<char*>(std::malloc(size)), size);
    std::memcpy(out.base, buf, size);
    uv_write(req, handle, &out, 1, on_write);
}

void on_connect(uv_connect_t* req, int status) {
    std::cout << "on_connect:" << status << std::endl;

    write_uv(&write_req, req->handle, "aaa");

    uv_close(reinterpret_cast<uv_handle_t*>(req->handle), on_close);// 这里感觉有问题，write 是异步的，应该要在 on_write 之后执行关闭。实际执行正常。
}

int main() {
    loop = uv_default_loop();

    uv_tcp_t* socket = new uv_tcp_t;
    uv_tcp_init(loop, socket);

    uv_connect_t* connect = new uv_connect_t;

    sockaddr_in dest;
    uv_ip4_addr("127.0.0.1", 12345, &dest);

    uv_tcp_connect(connect, socket, reinterpret_cast<const struct sockaddr*>(&dest), on_connect);

    uv_run(loop, UV_RUN_DEFAULT);
    uv_loop_close(loop);

    std::cin.get();
    return 0;
}
