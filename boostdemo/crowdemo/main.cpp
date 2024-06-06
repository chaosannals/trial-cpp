#include <iostream>
#include <crow.h>

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        return "Hello world";
    });

    CROW_ROUTE(app, "/json")([] {
        crow::json::wvalue x({ {"message", "Hello, World!"} });
        x["message2"] = "Hello, World.. Again!";
        return x;
    });

    // 这个宏有做类型检查，用常量表达式写了个语法分析，有点吊。
    // 支持 int uint float double  str string path
    CROW_ROUTE(app, "/hello/<int>/<string>")([](int count, const std::string &other) {
        if (count > 100)
            return crow::response(400);
        std::ostringstream os;
        os << count << " bottles of beer!";
        return crow::response(os.str());
    });


    CROW_ROUTE(app, "/add_json").methods("POST"_method)([](const crow::request& req) {
        auto x = crow::json::load(req.body);
        if (!x)
            return crow::response(crow::status::BAD_REQUEST); // same as crow::response(400)
        int sum = x["a"].i() + x["b"].i();
        std::ostringstream os;
        os << sum;
        return crow::response{ os.str() };
    });

    app.port(18080).multithreaded().run();
	return 0;
}
