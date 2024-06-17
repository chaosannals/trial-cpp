#include <iostream>
#include <cstring>
#include <uv.h>

uv_loop_t* loop;
uv_write_t echo_back;

void on_echo_back(uv_write_t* req, int status) {
    std::cout << "on_echo_back" << std::endl;
}

// uv_handle_t 是一个可以给其他 uv_* 句柄转换的，这样设计，类型丢失了。又是一个弱化类型的设计。
// 算是一个 加强版本的 void * 空类型指针，类型到这，丢了一半。
void alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
    std::cout << "alloc_buffer" << std::endl;
    *buf = uv_buf_init(reinterpret_cast<char*>(std::malloc(suggested_size)), suggested_size);
}

void echo_read(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf) {
    std::cout << "echo_read" << std::endl;

    if (nread < 0) {
        if (nread == UV_EOF) {
            std::cout << "echo_read eof." << std::endl;
        }
    }
    else if (nread > 0) {
        std::cout << "buf len:" << buf->len << " nread:" << nread << std::endl;
        uv_buf_t out = uv_buf_init(reinterpret_cast<char*>(std::malloc(nread)), nread);
        std::memcpy(out.base, buf->base, nread);
        uv_write(&echo_back, stream, &out, 1, on_echo_back);
    }

    if (buf->base) {
        std::free(buf->base);
    }
}

void on_new_connection(uv_stream_t* server, int status) {
    if (status < 0) {
        std::cout << "new conn err:" << uv_strerror(status) << std::endl;
    }

    uv_tcp_t* client = new uv_tcp_t;
    uv_tcp_init(loop, client);
    if (uv_accept(server, reinterpret_cast<uv_stream_t*>(client)) == 0) {
        uv_read_start(reinterpret_cast<uv_stream_t*>(client), alloc_buffer, echo_read);
    }
    else {
        uv_close(reinterpret_cast<uv_handle_t*>(client), nullptr);
    }
}

int main() {
    loop = uv_default_loop();

    uv_tcp_t server;
    uv_tcp_init(loop, &server);

    sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", 12345, &addr);

    uv_tcp_bind(&server, reinterpret_cast<const struct sockaddr*>(&addr), 0);
    int r = uv_listen(reinterpret_cast<uv_stream_t*>(&server), 1, on_new_connection);

    if (r) {
        std::cout << uv_strerror(r) << std::endl;
        return 1;
    }

    uv_run(loop, UV_RUN_DEFAULT);
    uv_loop_close(loop);

    std::cin.get();

    return 0;
}
