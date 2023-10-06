#include <asmjit/x86.h>
#include <stdio.h>
#include <iostream>

// AVX 512 在 intel 12 代 因为大小核开始被禁了，有主板可以关闭小核，就可以开启。

using namespace asmjit;

// 生成函数的声明
typedef void (*Func)(void*);

int main() {
    JitRuntime rt;                    // JIT 运行时。
    CodeHolder code;                  // 代码

    code.init(rt.environment(),       // 初始化
        rt.cpuFeatures());
    x86::Compiler cc(&code);          //  x86 编译器

    FuncNode* funcNode = cc.addFunc(FuncSignatureT<void, void*>());

    //启用 AVX and/or AVX-512.
    funcNode->frame().setAvxEnabled();
    funcNode->frame().setAvx512Enabled();

    
    x86::Gp addr = cc.newIntPtr("addr"); // 函数输入指针 void*
    x86::Zmm vreg = cc.newZmm("vreg"); // 512bit 寄存器

    funcNode->setArg(0, addr); // 设置参数关联

    cc.vmovdqu32(vreg, x86::ptr(addr)); // 地址内数据写入寄存器
    cc.vpaddq(vreg, vreg, vreg); // vreg + vreg ，结果是双倍
    cc.vmovdqu32(x86::ptr(addr), vreg); // 寄存器数据写回内存地址

    cc.endFunc(); // 结束函数
    cc.finalize(); // 完结编译
    // 

    Func fn;
    Error err = rt.add(&fn, &code);   // 把生成代码加入运行时
    if (err) return 1;

    // 因为使用了 512bit 所以 64 * 8 = 512 是固定大小的，不然可能内存溢出。
    uint64_t data[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    fn(data); // 调用。

    std::cout << "result 0:" << data[0] << std::endl;

    //printf("%llu\n", (unsigned long long)data[0]);

    rt.release(fn);                   // 释放

    std::cin.get();
    return 0;
}
