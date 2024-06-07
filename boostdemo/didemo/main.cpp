#include <iostream>
#include <boost/di.hpp>

class ctor {
public:
    explicit ctor(int i, double d) : i(i), d(d) {}
    int i;
    double d;
};

struct aggregate {
    double d;
};

struct interface {
    virtual ~interface() noexcept = default;
    virtual int get() const = 0;
};

class implementation : public interface {
public:
    int get() const override { return 4212; }
};

class example {
public:
    example(aggregate a, const ctor& c, std::shared_ptr<interface> i) {
        std::cout << "a.d" << a.d << std::endl
            << " c.i:" << c.i << std::endl
            << "c.d:" << c.d << std::endl
            << "i->get:" << i->get() << std::endl;
    };
};


int main() {
    using namespace boost::di;
    const auto injector = make_injector(
        // 这2个有点离谱，居然把 int double 注入到结构体，
        // 这个只带类型，如果多个导致所有 基础类型变成 相同的绑定值。
        bind<int>.to(42),
        bind<double>.to(87.0),

        // 正常的依赖注入
        bind<interface>.to<implementation>()
    );

    injector.create<example>();
    std::cin.get();
    return 0;
}
