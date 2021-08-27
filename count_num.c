#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    int number = 10000, backup, temp;
    asm("movl %%edx, %0" : "=r" (backup));
    asm("movl %0, %%edx" :  : "r"(number) );
    asm("\t movl %%edx,%0" : "=r"(temp));
    asm("movl $22 , %eax;");
    asm("int $64");
    asm("movl %0, %%edx" :  : "r"(backup) );
    exit();
}