#include <barrier.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <file.h>
#include <ulib.h>
#include <asynccall.h>

// #define BUFFER_ENTRIES (64)
#define BS (0x1000)
#define INSIZE (0x1000000 + BS)
#define ID_MAX (INSIZE / BS)
char buf[BS];
int FD;
int init_buffer(char *buf, int *check)
{
    int i;
    for (i = 0; i < BS; ++i)
    {
        buf[i] = (char )i;
    }
    return 0;
}

int write_file(char *buf)
{
    int i = 0;
    for(i = 0; i < ID_MAX; i++) {
        if(sys_write(FD, buf, BS) != BS) {
            return 1;
        }
    }
    cputs("write check over");
    return 0;
}

int main(int argc, char *argv[])
{
    int ret = 0;
    FD = open("tmp.txt", O_RDWR | O_CREAT);
    if (FD < 0)
    {
        cputs("open file error");
        return FD;
    }
    ret = write_file(buf);
    if (ret != 0)
        return ret;
    return 0;
}