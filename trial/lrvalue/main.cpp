#include <iostream>

struct test_block {
	test_block() {
		std::cout << "被构造了" << std::endl;
	}
	test_block(const test_block& other) {
		std::cout << "被拷贝了" << std::endl;
	}
};

struct tester_t {
	int v;
	test_block *b;
	tester_t(): v(2000) {
		b = new test_block;
		std::cout << "构造函数" << std::endl;
	}
	tester_t(const tester_t& other):v(other.v) {
		b = new test_block(*other.b);
		std::cout << "拷贝构造函数" << std::endl;
	}
	tester_t(tester_t &&other) :v(other.v),b(other.b) {
		other.b = nullptr;
		std::cout << "转移构造函数" << std::endl;
	}
	~tester_t() {
		if (nullptr != b) {
			delete b;
		}
	}
};

tester_t right_value(tester_t&& t) {
	std::cout << "右值" << std::endl;
	t.v = 1000;
	return std::forward<tester_t>(t);
}

tester_t left_value(const tester_t& t) {
	std::cout << "左值" << std::endl;
	return t;
}

int main() {
	tester_t t;
	tester_t l = left_value(t);
	tester_t r = right_value(std::move(t));
	std::cout << l.v << " | " << r.v << std::endl;
}