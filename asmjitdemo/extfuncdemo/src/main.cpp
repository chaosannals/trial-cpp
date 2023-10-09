#include <iostream>
#include <cstdio>
#include <asmjit/x86.h>

typedef void (*my_func_t)();

char text1[] = "Hello text 1 %s and %d";
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
    cc.mov(fn, (std::uint64_t)std::printf);
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

int main() {
    using namespace asmjit;

    JitRuntime rt;
    

    auto my_call_printf = initCallStdPrintf(rt);

    my_call_printf();

    rt.release(my_call_printf);

    std::cin.get();
    return 0;
}
