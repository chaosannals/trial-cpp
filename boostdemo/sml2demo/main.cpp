#include <iostream>
#include <sml2>

// 这个需要 C++20 且 VS 不支持的语法，必须奇幻 clang 或者 GCC 才能编译通过。（使用 x64-Clang-Debug）

// events
struct connect {};
struct ping { bool valid = false; };
struct established {};
struct timeout {};
struct disconnect {};

int main() {
    // state machine
    sml::sm connection = [] {
        // guards
        auto is_valid = [](const auto& event) { return event.valid; };

        // actions
        auto establish = [] { std::puts("establish"); };
        auto close = [] { std::puts("close"); };
        auto setup = [] { std::puts("setup"); };

        using namespace sml::dsl;
        /**
         * src_state + event [ guard ] / action = dst_state
         */
        return transition_table{
          *"Disconnected"_s + event<connect> / establish = "Connecting"_s,
           "Connecting"_s + event<established> = "Connected"_s,
           "Connected"_s + event<ping>[is_valid] / setup,
           "Connected"_s + event<timeout> / establish = "Connecting"_s,
           "Connected"_s + event<disconnect> / close = "Disconnected"_s,
        };
        };

    connection.process_event(connect{});
    connection.process_event(established{});
    connection.process_event(ping{ .valid = true });
    connection.process_event(disconnect{});
    return 0;
}
