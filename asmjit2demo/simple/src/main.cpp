#include <asmjit/x86.h>
#include <iostream>

using namespace asmjit;

typedef int (*Func)(void);

int main() {
    JitRuntime rt;
    CodeHolder code;

    code.init(rt.environment(), rt.cpuFeatures());

    x86::Assembler a(&code);

    a.mov(x86::eax, 1);  // Emits 'mov eax, 1' - moves one to 'eax' register.
    a.ret();             // Emits 'ret'        - returns from a function.

    Func fn;
    Error err = rt.add(&fn, &code);

    if (err) {
        printf("AsmJit failed: %s\n", DebugUtils::errorAsString(err));
        return 1;
    }

    int result = fn();
    printf("%d\n", result);
    rt.release(fn);


    std::cin.get();

    return 0;
}
