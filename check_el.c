#include <stdio.h>
#include <stdint.h>

int main() {
    uint64_t el;
    asm volatile("mrs %0, CurrentEL" : "=r"(el));
    printf("当前 Exception Level: EL%llu\n", el >> 2);
    return 0;
}
