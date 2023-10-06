#include <iostream>
#include <stack>
#include <asmjit/x86.h>

typedef double (*my_func)();


extern "C" {
    struct ast {
        int nodetype;
        double number;
        int offset;
        struct ast* l;
        struct ast* r;
    };
    int yyparse();
    void yyerror(char* s, ...);
}

// TODO XMM SIMD 指令汇编
asmjit::x86::Xmm walk_jit(struct ast* a, asmjit::x86::Compiler &cc) {
    using namespace asmjit;

    switch (a->nodetype) {
    case 'N': {
        auto n = cc.newDoubleConst(ConstPoolScope::kLocal, a->number);
        auto r = cc.newXmmSd();
        cc.movsd(r, n);
        return r;
    }
    case 'M': {
        auto n = cc.newDoubleConst(ConstPoolScope::kLocal, 0.0);
        auto r = walk_jit(a->l, cc);
        cc.subsd(r, n);
        return r;
    }
    case '+': {
        auto left = walk_jit(a->l, cc);
        auto right = walk_jit(a->r, cc);
        cc.addsd(left, right);
        return left;
    }
    case '-': {
        auto left = walk_jit(a->l, cc);
        auto right = walk_jit(a->r, cc);
        cc.subsd(left, right);
        return left;
    }
    case '*': {
        auto left = walk_jit(a->l, cc);
        auto right = walk_jit(a->r, cc);
        cc.mulsd(left, right);
        return left;
    }
    case '/': {
        auto left = walk_jit(a->l, cc);
        auto right = walk_jit(a->r, cc);
        cc.divsd(left, right);
        return left;
    }
    default:
        printf("internal error: bad node $c\n", a->nodetype);
        return cc.newXmm();
    }
}

extern "C" void run_jit(struct ast* a) {
    using namespace asmjit;

    if (!a) {
        yyerror("internal error, null eval");
        return;
    }

    JitRuntime runtime;
    CodeHolder code;
    code.init(runtime.environment(), runtime.cpuFeatures());
    x86::Compiler cc(&code);
    Zone zone(1024);
    ConstPool constPool(&zone);

    auto myfunc = cc.addFunc(FuncSignatureT<double>());

    // 走树
    auto result = walk_jit(a, cc);
    cc.ret(result);

    cc.endFunc();
    cc.finalize();

    my_func func;
    auto error = runtime.add(&func, &code);

    std::cout << "jit error: " << error << std::endl;

    auto r = func();

    runtime.release(func);

    std::cout << "jit result: " << r << std::endl;
    
    return;
}

int main() {
    while (1) {
        int code = yyparse();
        std::cout << "code: " << code << std::endl;
    }
    return 0;
}
