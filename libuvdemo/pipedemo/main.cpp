#include <iostream>
#include <cstdlib>
#include <cstring>
#include <uv.h>

uv_pipe_t stdin_pipe;
uv_pipe_t stdout_pipe;
uv_pipe_t file_pipe;

typedef struct {
    uv_write_t req;
    uv_buf_t buf;
} write_req_t ;

void free_write_req(uv_write_t* req) {
    std::cout << "free_write_req" << std::endl;
    write_req_t* wr = reinterpret_cast<write_req_t*>(req);
    std::free(wr->buf.base);
    std::free(wr);
}

void on_stdout_write(uv_write_t* req, int status) {
    free_write_req(req);
}

void on_file_write(uv_write_t* req, int status) {
    free_write_req(req);
}

void write_data(uv_stream_t* dest, size_t size, uv_buf_t buf, uv_write_cb cb) {
    std::cout << "write_data" << std::endl;
    write_req_t *req = reinterpret_cast<write_req_t*>(std::malloc(sizeof(write_req_t)));
    req->buf = uv_buf_init(reinterpret_cast<char*>(std::malloc(size)), size);
    std::memcpy(req->buf.base, buf.base, size);
    uv_write(&req->req, dest, &req->buf, 1, cb);
}

// uv_handle_t 是一个可以给其他 uv_* 句柄转换的，这样设计，类型丢失了。又是一个弱化类型的设计。
// 算是一个 加强版本的 void * 空类型指针，类型到这，丢了一半。
void alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
    std::cout << "alloc_buffer" << std::endl;
    *buf = uv_buf_init(reinterpret_cast<char*>(std::malloc(suggested_size)), suggested_size);
}

// uv_stream_t 也是一个类似 基类或者接口的设计，uv_tcp_t uv_pipe_t uv_tty_t 可以强转放到这个
void read_stdin(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf) {
    std::cout << "read_stdin" << std::endl;

    if (nread < 0) {
        if (nread == UV_EOF) {
            uv_close(reinterpret_cast<uv_handle_t *>(&stdin_pipe), nullptr);
            uv_close(reinterpret_cast<uv_handle_t*>(&stdout_pipe), nullptr);
            uv_close(reinterpret_cast<uv_handle_t*>(&file_pipe), nullptr);
        }
    }
    else if (nread > 0) {
        write_data(reinterpret_cast<uv_stream_t*>(&stdout_pipe), nread, * buf, on_stdout_write);
        write_data(reinterpret_cast<uv_stream_t*>(&file_pipe), nread, *buf, on_file_write);
    }

    if (buf->base) {
        std::free(buf->base);
    }
}

int main() {
    uv_loop_t* loop = uv_default_loop();

    // Linux 下 正常，Windows 下可能因为权限问题，不能拿到 stdin stdout 的。
    int stdin_i_r = uv_pipe_init(loop, &stdin_pipe, 0);
    int stdin_o_r = uv_pipe_open(&stdin_pipe, 0); // fd=0 stdin

    int stdout_i_r = uv_pipe_init(loop, &stdout_pipe, 0);
    int stdout_o_r = uv_pipe_open(&stdout_pipe, 1); // fd=1 stdout

    std::cout << "stdin:" << uv_err_name(stdin_i_r) << " | " << uv_err_name(stdin_o_r) << std::endl
        << "stdout:" << uv_err_name(stdout_i_r) << " | " << uv_err_name(stdout_o_r) << std::endl;

    uv_fs_t open_req;
    int fd = uv_fs_open(loop, &open_req, "pipedemo.txt", O_CREAT | O_RDWR, 0644, nullptr);
    uv_pipe_init(loop, &file_pipe, 0);
    uv_pipe_open(&file_pipe, fd);

    int rsr = uv_read_start(reinterpret_cast<uv_stream_t*>(&stdin_pipe), alloc_buffer, read_stdin);
    std::cout << "uv_read_start:" << uv_err_name(rsr) << std::endl;

    uv_run(loop, UV_RUN_DEFAULT);
    uv_loop_close(loop);

    std::cin.get();

    //std::string cmd;
    //while (cmd.find("quit") == std::string::npos) {
    //    std::cin >> cmd;
    //}
    return 0;
}
