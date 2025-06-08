#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <setjmp.h>

static sigjmp_buf jmpbuf;

void handle_sigill(int sig) {
    siglongjmp(jmpbuf, 1);  // 跳转回 setjmp
}

int main() {
    uint64_t el;
    
    // 注册 SIGILL 处理器
    signal(SIGILL, handle_sigill);
    
    // 尝试执行 MRS 指令
    if (sigsetjmp(jmpbuf, 1) == 0) {
        // 如果没有触发 SIGILL，说明可以读取 CurrentEL
        asm volatile("mrs %0, CurrentEL" : "=r"(el));
        printf("当前 Exception Level: EL%llu\n", el >> 2);
    } else {
        // 如果触发 SIGILL，说明在 EL0（用户空间）
        printf("当前在用户模式 (EL0)，无法读取 CurrentEL\n");
    }
    
    return 0;
}
