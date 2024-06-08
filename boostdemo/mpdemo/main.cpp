#include <iostream>
// 居然按标准库规格，不加 .h 做文件名。。。
#include <mp>

namespace dsl {
    constexpr auto filter = [](auto fn) {
        return[fn]<class... Ts> {
            mp::vector<mp::meta_t, sizeof...(Ts)> r;
            ([&] {
                if (fn.template operator() < Ts > ()) {
                    r.push_back(mp::meta<Ts>);
                }
                }(), ...);
            return r;
        };
        };

    constexpr auto transform = [](auto fn) {
        return[]<class... Ts> {
            return mp::vector{ mp::meta<decltype(fn.template operator() < Ts > ())>... };
        };
        };

    constexpr auto reverse = []<class... Ts> {
        mp::vector v{ mp::meta<Ts>... };
        mp::vector<mp::meta_t, sizeof...(Ts)> r;
        for (auto i = 0u; i < v.size(); ++i) {
            r.push_back(v[v.size() - i - 1]);
        }
        return r;
    };


    template<auto N>
    constexpr auto take = []<class... Ts> {
        mp::vector v{ mp::meta<Ts>... };
        mp::vector<mp::meta_t, N> r;
        for (auto i = 0; i < N; ++i) {
            r.push_back(v[i]);
        }
        return r;
    };

    template<template<class...> class T, class... Ts>
    constexpr auto operator|(T<Ts...>, auto fn) {
        return mp::apply<T>([fn] { return fn.template operator() < Ts... > (); });
    }
} // namespace dsl

namespace detail {
    template<class...> struct type_list {
        constexpr bool operator==(type_list) const { return true; }
        template<class T> constexpr bool operator==(T) const { return false; }
    };
}

template<class... Ts> detail::type_list<Ts...> type_list{ };

int main() {
    using namespace dsl;
    constexpr auto v =
        type_list<int, const double, float>
        | filter([]<class T> { return not std::is_const_v<T>; })
        | transform([]<class T>() -> T* { })
        | reverse
        | take<1>
        ;

    static_assert(type_list<float*> == v);

    std::cin.get();

    return 0;
}
