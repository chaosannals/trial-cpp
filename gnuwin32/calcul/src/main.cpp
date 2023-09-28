#include <iostream>

extern "C" int yyparse();

int main() {
    while (1) {
        int code = yyparse();
        std::cout << "code: " << code << std::endl;
    }
    return 0;
}
