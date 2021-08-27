#include "types.h"
#include "stat.h"
#include "user.h"

#define MAXFILELEN 128

int main(int argc, char *argv[]) {
    if(argc != 3){
        printf(1, "Bad input.\n");
        exit();
    }
    int backup;
    char* toBeSent = (char*) malloc (MAXFILELEN * sizeof(char));
    strcpy(toBeSent, argv[2]);    

    asm("movl %%edx, %0" : "=r" (backup));
    asm("movl %0, %%edx" :  : "r"(toBeSent));
    asm("movl $23 , %eax;");
    asm("int $64");
    asm("movl %0, %%edx" :  : "r"(backup) );

    exit();
}