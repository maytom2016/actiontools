#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <setjmp.h>

static sigjmp_buf jmpbuf;

void handle_sigill(int sig) {
    siglongjmp(jmpbuf, 1);
}

int main() {
    uint64_t el;
    
    signal(SIGILL, handle_sigill);
    
    if (sigsetjmp(jmpbuf, 1) {
        printf("当前在用户模式 (EL0)\n");
    } else {
        asm volatile("mrs %0, CurrentEL" : "=r"(el));
        printf("当前 Exception Level: EL%llu\n", el >> 2);
    }
    
    return 0;
}
