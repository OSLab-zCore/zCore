#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ulib.h>
#include <syscall.h>

int main(void) {
    if(fork() == 0) {
        char name[] = "/bin/busyboxls";
        sys_exec(name, 0, NULL);
    }
    // if(fork() == 0) {
    //     cputs("child process[1], wait for keyboard input.\n wait for next\n");
    //     for(int i = 0; i < 100; i++) {
    //         char c = getchar();
    //         cprintf("char[%d] = %c, wait for next\n", i, c);
    //     }
    //     cputs("child process[1] over");
    // }
    sys_block_in_kernel();
    return 0;
}