#include <asmjit/x86.h>
#include <iostream>
#include <cstdint>

using namespace asmjit;

typedef float (*my_func_t)(float, float, std::uint32_t);

static void exampleUseOfIndirectJump(x86::Compiler& cc) {
    FuncNode* funcNode = cc.addFunc(FuncSignatureT<float, float, float, std::uint32_t>(CallConvId::kHost));

    // 函数参数
    x86::Xmm a = cc.newXmmSs("a");
    x86::Xmm b = cc.newXmmSs("b");
    x86::Gp op = cc.newUInt32("op");

    x86::Gp target = cc.newIntPtr("target");
    x86::Gp offset = cc.newIntPtr("offset");

    Label L_Table = cc.newLabel();
    Label L_Add = cc.newLabel();
    Label L_Sub = cc.newLabel();
    Label L_Mul = cc.newLabel();
    Label L_Div = cc.newLabel();
    Label L_End = cc.newLabel();

    funcNode->setArg(0, a);
    funcNode->setArg(1, b);
    funcNode->setArg(2, op);

    // Jump annotation is a building block that allows to annotate all possible targets where `jmp()` can
    // jump. It then drives the CFG construction and liveness analysis, which impacts register allocation.
    // 跳转注解可以把多个标签联系在一起
    JumpAnnotation* annotation = cc.newJumpAnnotation();
    annotation->addLabel(L_Add);
    annotation->addLabel(L_Sub);
    annotation->addLabel(L_Mul);
    annotation->addLabel(L_Div);

    // Most likely not the common indirect jump approach, but it
    // doesn't really matter how final address is calculated. The
    // most important path using JumpAnnotation with `jmp()`.
    cc.lea(offset, x86::ptr(L_Table));
    if (cc.is64Bit())
        cc.movsxd(target, x86::dword_ptr(offset, op.cloneAs(offset), 2));
    else
        cc.mov(target, x86::dword_ptr(offset, op.cloneAs(offset), 2));
    cc.add(target, offset);
    cc.jmp(target, annotation);

    // Acts like a switch() statement in C.
    cc.bind(L_Add);
    cc.addss(a, b);
    cc.jmp(L_End);

    cc.bind(L_Sub);
    cc.subss(a, b);
    cc.jmp(L_End);

    cc.bind(L_Mul);
    cc.mulss(a, b);
    cc.jmp(L_End);

    cc.bind(L_Div);
    cc.divss(a, b);

    cc.bind(L_End);
    cc.ret(a);

    cc.endFunc();

    // Relative int32_t offsets of `L_XXX - L_Table`.
    cc.bind(L_Table);
    cc.embedLabelDelta(L_Add, L_Table, 4);
    cc.embedLabelDelta(L_Sub, L_Table, 4);
    cc.embedLabelDelta(L_Mul, L_Table, 4);
    cc.embedLabelDelta(L_Div, L_Table, 4);
}

int main() {
    JitRuntime rt;
    CodeHolder code;

    code.init(rt.environment(),
        rt.cpuFeatures());
    x86::Compiler cc(&code);

    exampleUseOfIndirectJump(cc);

    cc.finalize();

    my_func_t my_func;
    rt.add(&my_func, &code);

    float a = 123.4f;
    float b = 567.9f;
    std::cout << "result jit add: " << my_func(a, b, 0) << std::endl
        << "result c add: " << a + b << std::endl
        << "result jit sub: " << my_func(a, b, 1) << std::endl
        << "result c sub: " << a - b << std::endl
        << "result jit mul: " << my_func(a, b, 2) << std::endl
        << "result c mul: " << a * b << std::endl
        << "result jit div: " << my_func(a, b, 3) << std::endl
        << "result c div: " << a / b << std::endl
        << std::endl;

    std::cin.get();

    return 0;
}
