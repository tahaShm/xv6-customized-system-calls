#include "types.h"
#include "stat.h"
#include "user.h"
#include "date.h"


int main(int argc, char* argv[]) {
    if(argc != 2){
        printf(1, "Bad input.\n");
        exit();
    }
    int backup;

    asm("movl %%edx, %0" : "=r" (backup));
    asm("movl %0, %%edx" :  : "r"(atoi(argv[1])));
    asm("movl $26 , %eax;");
    asm("int $64");
    asm("movl %0, %%edx" :  : "r"(backup));
    
    exit();
}