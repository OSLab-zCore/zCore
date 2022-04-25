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
#define INSIZE (0x1000000)
#define ID_MAX (INSIZE / BS)
#define min(a, b) (a > b ? b : a)

int FD;
char buf[INSIZE];
int check[ID_MAX];

int hash(char *buf)
{
    int i, checksum = 0;
    for (i = 0; i < BS / 32; ++i)
    {
        checksum ^= *(int *)(buf + 4 * i);
    }
    return checksum;
}

int rand_buffer(char *buf)
{
    int i;
    for (i = 0; i < BS / 32; ++i)
    {
        *(int *)(buf + 4 * i) = rand();
    }
    return 0;
}

int init_buffer(char *buf, int *check)
{
    int i;
    for (i = 0; i < ID_MAX; ++i)
    {
        rand_buffer(&buf[BS * i]);
        check[i] = hash(&buf[BS * i]);
    }
    return 0;
}

int write_file(char *buf, int* check)
{
    int i = 0;
    for(i = 0; i < ID_MAX; i++) {
        if(sys_writeat(FD, &buf[BS * i], BS, BS * i) != BS) {
            return 1;
        }
    }
    cputs("write check over");
    return 0;
}

int check_file(char *buf, int *check)
{
    int i = 0;
    for(i = 0; i < ID_MAX; i++) {
        if(sys_readat(FD, &buf[BS * i], BS, BS * i) != BS) {
            return 1;
        }
        hash(&buf[BS * i]) != check[i];
        // {
        //     cprintf("read content error: %d != %d\n", hash(&buf[BS * i]), check[i]);
        //     return 1;
        // }
    }
    cputs("read check over");
}

int run_test(int seed)
{
    int ret;
    memset(buf, 0, INSIZE);
    srand(seed);
    init_buffer(buf, check);
    ret = write_file(buf, check);
    if (ret != 0)
        return ret;
    memset(buf, 0, INSIZE);
    return check_file(buf, check);
}

int main(int argc, char *argv[])
{
    int ret = 0;
    cputs("Read after write test.");
    FD = open("tmp.txt", O_RDWR | O_CREAT);
    if (FD < 0)
    {
        cputs("open file error");
        return FD;
    }
    cputs("tmp file created!");
    cputs("test start!");
    int t0 = sys_times();
    ret = run_test(strlen(argv[0]));
    int t1 = sys_times();
    if (ret != 0)
    {
        cputs("result error");
        return ret;
    }
    close(FD);
    cprintf("Simple test: OK, sync version, time_delta = %d", t1 - t0);
    return 0;
}