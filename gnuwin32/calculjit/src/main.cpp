#include "calculjit.h"
#include <iostream>
#include <asmjit/x86.h>

typedef double (*my_func)();


extern "C" int yyparse();

void walk_jit(struct ast* a,asmjit::ConstPool &constPool) {
    // TODO

    switch (a->nodetype) {
    case 'N':
        size_t offset;
        constPool.add(&a->number, sizeof(double), offset);
        a->offset = offset;
        break;
    case 'M':
        walk_jit(a->l, constPool);
        break;
    case '+':
        walk_jit(a->l, constPool);
        walk_jit(a->r, constPool);
        break;
    case '-':
        walk_jit(a->l, constPool);
        walk_jit(a->r, constPool);
        break;
    case '*':
        walk_jit(a->l, constPool);
        walk_jit(a->r, constPool);
        break;
    case '/':
        walk_jit(a->l, constPool);
        walk_jit(a->r, constPool);
        break;
    default: printf("internal error: bad node $c\n", a->nodetype);
    }
}

void run_jit(struct ast* a) {
    using namespace asmjit;

    if (!a) {
        yyerror("internal error, null eval");
        return;
    }

    JitRuntime runtime;
    CodeHolder code;
    code.init(runtime.environment());
    x86::Compiler cc(&code);
    Zone zone(1024);
    ConstPool constPool(&zone);

    auto myfunc = cc.addFunc(FuncSignatureT<double>());

    // 走树
    walk_jit(a, constPool);

    cc.endFunc();
    cc.finalize();

    my_func func;
    auto error = runtime.add(&func, &code);

    auto r = func();

    runtime.release(func);

    std::cout << "jit error: " << error << std::endl
        << "jit result: " << r << std::endl;
    
    return;
}

int main() {
    while (1) {
        int code = yyparse();
        std::cout << "code: " << code << std::endl;
    }
    return 0;
}
