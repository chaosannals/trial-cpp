#include <iostream>
#include <cstdio>
#include <asmjit/x86.h>

typedef void (*my_func_t)();
typedef int (*my_func_2_t)();

char text1[] = "Hello text 1 %s and %d\r\n";
char text1args1[] = "xxxxxx";

my_func_t initCallStdPrintf(asmjit::JitRuntime &rt) {
    using namespace asmjit;
    CodeHolder code;

    code.init(rt.environment(),
        rt.cpuFeatures());
    x86::Compiler cc(&code);

    cc.addFunc(FuncSignatureT<void>());

    x86::Gp fn = cc.newUIntPtr();
    auto fa1 = cc.newIntPtr();
    auto fa2 = cc.newIntPtr();
    auto fa3 = cc.newInt32();
    auto fa3i = cc.newInt32Const(ConstPoolScope::kLocal, 1234);
    cc.mov(fn, std::printf);
    cc.mov(fa1, text1);
    cc.mov(fa2, text1args1);
    cc.mov(fa3, fa3i);
    InvokeNode* printfCall;
    cc.invoke(&printfCall, fn, FuncSignatureT<int, char*, char*, int>(CallConvId::kCDecl));
    printfCall->setArg(0, fa1);
    printfCall->setArg(1, fa2);
    printfCall->setArg(2, fa3);

    cc.endFunc();
    cc.finalize();

    my_func_t my_call_printf;
    rt.add(&my_call_printf, &code);

    return my_call_printf;
}

int my_custom_func(int a, int b) {
    int r = a + a / b;
    std::cout << "my_custom_func: a:" << a << " b: " << b << " (r = a + a / b): " << r << std::endl;
    return r;
}

my_func_2_t initCallMyCustomFunc(asmjit::JitRuntime& rt) {
    using namespace asmjit;
    CodeHolder code;

    code.init(rt.environment(),
        rt.cpuFeatures());
    x86::Compiler cc(&code);

    cc.addFunc(FuncSignatureT<int>());

    x86::Gp fn = cc.newUIntPtr();
    auto fa1 = cc.newInt32();
    auto fa2 = cc.newInt32();
    auto fr = cc.newInt32();
    auto fa1i1 = cc.newInt32Const(ConstPoolScope::kLocal, 100);

    cc.mov(fn, my_custom_func);
    cc.mov(fa1, fa1i1);
    cc.mov(fa2, 4);

    InvokeNode* invokeNode;
    cc.invoke(&invokeNode, fn, FuncSignatureT<int, int, int>(CallConvId::kHost));
    invokeNode->setArg(0, fa1);
    invokeNode->setArg(1, fa2);
    invokeNode->setRet(0, fr);

    cc.ret(fr);
    cc.endFunc();
    cc.finalize();

    my_func_2_t my_func;
    rt.add(&my_func, &code);
    return my_func;
}

int main() {
    using namespace asmjit;

    JitRuntime rt;
    

    auto my_call_printf = initCallStdPrintf(rt);
    auto my_call_custom_func = initCallMyCustomFunc(rt);

    my_call_printf();
    auto f2r = my_call_custom_func();

    rt.release(my_call_printf);
    rt.release(my_call_custom_func);

    std::cout << "my_call_custom_func result: " << f2r << std::endl;

    std::cin.get();
    return 0;
}
