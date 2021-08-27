#include "types.h"
#include "stat.h"
#include "user.h"

// #define MAXCHILDREN 11

int main(int argc, char* argv[]) {
    if(argc != 2){
        printf(1, "Bad input.\n");
        exit();
    }
    int backup;    
    int children;

    asm("movl %%edx, %0" : "=r" (backup));
    asm("movl %0, %%edx" :  : "r"(atoi(argv[1])));
    // asm("movl $25 , %eax;");
    // asm("int $64");
    children = get_children();
    printf(2, "Children are : %d\n", children);
    asm("movl %0, %%edx" :  : "r"(backup) );
    
    exit();
}