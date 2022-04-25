#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ulib.h>
#include <syscall.h>

int main(void) {
    if(fork() == 0) {
        cputs("child process[0], wait for time interrupt.");
        struct timespec time = { .tv_sec = 0, .tv_nsec = 5e8};
        for(int i = 0; i < 200; i++) {
            cprintf("wait for time interrupts %d\n", i);
            sleep(&time);
        }
        cputs("child process[0] over");
        exit(0);
    }
    if(fork() == 0) {
        cputs("child process[1], wait for keyboard input.\n wait for next\n");
        for(int i = 0; i < 100; i++) {
            char c = getchar();
            cprintf("char[%d] = %c, wait for next\n", i, c);
        }
        cputs("child process[1] over");
    }
    sys_block_in_kernel();
    return 0;
}