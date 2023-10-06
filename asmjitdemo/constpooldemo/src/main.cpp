#include <asmjit/x86.h>
#include <iostream>

using namespace asmjit;

typedef int (*my_func_t)();

int main() {
    JitRuntime rt;
    CodeHolder code;

    code.init(rt.environment(),
        rt.cpuFeatures());
    x86::Compiler cc(&code);

    cc.addFunc(FuncSignatureT<int>());

    x86::Gp v0 = cc.newGpd("v0"); // 
    x86::Gp v1 = cc.newGpd("v1");

    // 使用 本地常量池 kLocal 只能在当函数内使用
    x86::Mem c0 = cc.newInt32Const(ConstPoolScope::kLocal, 200);
    x86::Mem c1 = cc.newInt32Const(ConstPoolScope::kLocal, 33);

    // 使用 全局常量池 kGlobal 可以跨多个方法，直到 finalize 被调用。
    //x86::Mem c0 = cc.newInt32Const(ConstPoolScope::kGlobal, 200);
    //x86::Mem c1 = cc.newInt32Const(ConstPoolScope::kGlobal, 33);

    cc.mov(v0, c0);
    cc.mov(v1, c1);
    cc.add(v0, v1);

    cc.ret(v0);
    cc.endFunc();

    cc.finalize();

    my_func_t my_func;
    auto err = rt.add(&my_func, &code);
    if (err) return 1;

    std::cout << "result: " << my_func() << std::endl;

    std::cin.get();

    return 0;
}
