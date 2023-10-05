#include <asmjit/asmjit.h>
#include <stdio.h>
#include <iostream>

using namespace asmjit;

// 导出函数类型
typedef void (*MemCpy32)(uint32_t* dst, const uint32_t* src, size_t count);

int main() {
    JitRuntime rt;                    // JIT 运行时。
    CodeHolder code;                  // 代码管理对象。

    code.init(rt.environment(), rt.cpuFeatures());
    x86::Compiler cc(&code);          // x86 编译器

    FuncNode* funcNode = cc.addFunc(  // 开始一个函数的定义。
        FuncSignatureT<void,            //   返回值 void ，此处没有返回值
        uint32_t*,                    //   参数1 uint32_t* (machine reg-size).
        const uint32_t*,              //   参数2 uint32_t* (machine reg-size).
        size_t>());                   //   参数3 size_t    (machine reg-size).

    Label L_Loop = cc.newLabel();     // 定义循环体开始标签， bind 的时候才启用。
    Label L_Exit = cc.newLabel();     // 定义循环体结束标签， bind 的时候才启用。

    // 定义参数寄存器
    x86::Gp dst = cc.newIntPtr("dst");// Create `dst` register (destination pointer).
    x86::Gp src = cc.newIntPtr("src");// Create `src` register (source pointer).
    x86::Gp i = cc.newUIntPtr("i");   // Create `i` register (loop counter).


    funcNode->setArg(0, dst);         // Assign `dst` argument.
    funcNode->setArg(1, src);         // Assign `src` argument.
    funcNode->setArg(2, i);           // Assign `i` argument.


    cc.test(i, i);                    // Early exit if length is zero.
    cc.jz(L_Exit);

    cc.bind(L_Loop);                  // Bind the beginning of the loop here.

    x86::Gp tmp = cc.newInt32("tmp"); // Copy a single dword (4 bytes).
    cc.mov(tmp, x86::dword_ptr(src)); // Load DWORD from [src] address.
    cc.mov(x86::dword_ptr(dst), tmp); // Store DWORD to [dst] address.

    cc.add(src, 4);                   // Increment `src`.
    cc.add(dst, 4);                   // Increment `dst`.

    cc.dec(i);                        // Loop until `i` is non-zero.
    cc.jnz(L_Loop);

    cc.bind(L_Exit);                  // Label used by early exit.
    cc.endFunc();                     // End of the function body.

    cc.finalize();                    // Translate and assemble the whole 'cc' content.
    // ----> x86::Compiler is no longer needed from here and can be destroyed <----

    // Add the generated code to the runtime.
    MemCpy32 memcpy32;
    Error err = rt.add(&memcpy32, &code);

    // Handle a possible error returned by AsmJit.
    if (err)
        return 1;
    // ----> CodeHolder is no longer needed from here and can be destroyed <----

    // Test the generated code.
    uint32_t input[6] = { 1, 2, 3, 5, 8, 13 };
    uint32_t output[6];
    memcpy32(output, input, 6);

    for (uint32_t i = 0; i < 6; i++) {
        printf("%d\n", output[i]);
    }

    rt.release(memcpy32);

    std::cin.get();
    return 0;
}