#include <asmjit/x86.h>
#include <stdio.h>
#include <iostream>

using namespace asmjit;

// 生成函数声明
typedef int (*Func)(void);

// 栈相关示例
int main() {
    JitRuntime rt;
    CodeHolder code;

    code.init(rt.environment(),
        rt.cpuFeatures());
    x86::Compiler cc(&code);

    cc.addFunc(FuncSignatureT<int>());// 这里没有获取返回值 FuncNode*， 而是下面直接操作栈。

    x86::Gp p = cc.newIntPtr("p"); // 只是下面展示 lea 指令用的。
    x86::Gp i = cc.newIntPtr("i"); // 索引 i

    // 分配 256 bytes 的栈 ，4 bytes 对齐
    x86::Mem stack = cc.newStack(256, 4);

    // 一种形式上的绑定，根据 i 作为索引，取 stack 内大小为 1 byte 的数据。
    x86::Mem stackIdx(stack);         // Copy of stack with i added.
    stackIdx.setIndex(i);             // stackIdx <- stack[i].
    stackIdx.setSize(1);              // stackIdx <- byte ptr stack[i].

    // 只是展示 lea 指令，和下面的操作无关。取 stack 地址到 p
    cc.lea(p, stack);

    // i 清零  ，类似 xor eax,eax 这种。
    cc.xor_(i, i);

    Label L1 = cc.newLabel();
    Label L2 = cc.newLabel();

    // 第一次循环，填充栈。 从 0 递增，值就是索引值。
    cc.bind(L1);                      // L1:
    cc.mov(stackIdx, i.r8());         // stack[i] = uint8_t(i).

    cc.inc(i);                        // i++;
    cc.cmp(i, 256);                   // if (i < 256)
    cc.jb(L1);                        //   goto L1;

    // 第二次循环, 把栈中各个 bytes 的值累加到 sum
    x86::Gp sum = cc.newInt32("sum");
    x86::Gp val = cc.newInt32("val");

    // i, sum 清零
    cc.xor_(i, i);
    cc.xor_(sum, sum);

    cc.bind(L2);                     // L2:

    cc.movzx(val, stackIdx);          // val = uint32_t(stack[i]);
    cc.add(sum, val);                 // sum += val;

    cc.inc(i);                        // i++;
    cc.cmp(i, 256);                   // if (i < 256)
    cc.jb(L2);                        //   goto L2;

    cc.ret(sum); // 返回累加值 sum
    cc.endFunc();

    cc.finalize();

    Func func;
    Error err = rt.add(&func, &code);
    if (err) return 1;

    printf("asmjit result: Func() -> %d\n", func());

    rt.release(func);

    int c_sum = 0;
    for (int c_i = 0; c_i < 256; ++c_i) {
        c_sum += c_i;
    }

    std::cout << "c result: " << c_sum << std::endl;

    std::cin.get();
    return 0;
}
