#include <iostream>
#include <coroutine>

struct generator
{
    struct promise_type;
    using handle = std::coroutine_handle<promise_type>;
    struct promise_type
    {
        int current_value;
        static auto get_return_object_on_allocation_failure() { return generator{ nullptr }; }
        auto get_return_object() { return generator{ handle::from_promise(*this) }; }
        auto initial_suspend() { return std::suspend_always{}; }
        auto final_suspend() noexcept { return std::suspend_always{}; }
        void unhandled_exception() { std::terminate(); }
        void return_void() {}
        auto yield_value(int value)
        {
            current_value = value;
            return std::suspend_always{}; // 这是一个 awaiter 结构, 见第二篇文章
        }
    };
    bool move_next() {
        if (coro) {
            coro.resume();
            return !coro.done();
        }
        return false;
    }
    int current_value() { return coro.promise().current_value; }
    generator(generator const&) = delete;
    generator(generator&& rhs) noexcept : coro(rhs.coro) { rhs.coro = nullptr; }
    ~generator() { if (coro) coro.destroy(); }

private:
    generator(handle h) : coro(h) {}
    handle coro;
};

generator f() noexcept
{
    co_yield 1;
    co_yield 2;
}

int main()
{
    auto g = f(); // 停在 initial_suspend 那里
    while (g.move_next()) // 每次调用就停在下一个 co_await 那里
        std::cout << g.current_value() << std::endl;
    return std::cin.get();
}