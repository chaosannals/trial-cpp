#include <asmjit/x86.h>
#include <stdio.h>
#include <iostream>

using namespace asmjit;

// 生成函数声明
typedef uint32_t(*Fibonacci)(uint32_t x);

// f(0) = 1
// f(1) = 1
// f(x) = f(x-1) + f(x-2) x ∈[2,+∞)
//
int main() {
    JitRuntime rt;
    CodeHolder code;

    code.init(rt.environment(),
        rt.cpuFeatures());
    x86::Compiler cc(&code);

    FuncNode* funcNode = cc.addFunc(
        FuncSignatureT<int, int>());

    Label L_Exit = cc.newLabel();      // 结束标签 exit:
    Label L_Init = cc.newLabel();     // 斐波那契初始 0 1 项的值是 1
    x86::Gp x = cc.newUInt32();       // 函数参数 x
    x86::Gp y = cc.newUInt32();       // 暂存变量 y

    funcNode->setArg(0, x);    // 绑定参数 x

    // x < 2 就设置成 1
    cc.cmp(x, 2);
    cc.jge(L_Init); // x >= 2 跳过
    cc.mov(x, 1);

    cc.bind(L_Init);

    cc.cmp(x, 3);                     // x < 3 直接 跳转 exit:
    cc.jb(L_Exit);

    // f(x - 1)
    //cc.mov(y, x);                     // y 取 x 作为初始的值
    cc.dec(x);                        // 递减 x
    InvokeNode* fx1;           // 函数调用 点
    cc.invoke(&fx1,            //   - fx1 (output).
        funcNode->label(),              //   - 指定调用的函数标签
        FuncSignatureT<int, int>());    //   - 指定调用的函数结构声明斐波那契数列
    fx1->setArg(0, x);         // 设置参数 x
    fx1->setRet(0, y);         // 设置参数返回在 y 里


    // f(x - 2)
    cc.dec(x);                        // 递减 x
    InvokeNode* fx2;
    cc.invoke(
        &fx2,
        funcNode->label(),              //   - 指定调用的函数标签
        FuncSignatureT<int, int>()    //   - 指定调用的函数结构声明斐波那契数列
    );
    fx2->setArg(0, x);
    fx2->setRet(0, x); //设置参数返回在 x 里


    cc.add(x, y);                     // 把返回值 x 加上 y

    cc.bind(L_Exit);                  // 绑定 exit: 标签的位置
    cc.ret(x);                        // 返回 x.
    cc.endFunc();

    cc.finalize();
    
    // 这是个 斐波那契数列 的函数定义
    Fibonacci fib;
    Error err = rt.add(&fib, &code);
    if (err) return 1;

    // 输出值
    for (int i = 0; i < 20; ++i) {
        printf("Fib(%u) -> %u\n", i, fib(i));
    }

    rt.release(fib);

    std::cin.get();
    return 0;
}
