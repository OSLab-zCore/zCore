#include <asynccall.h>
#include <barrier.h>
#include <file.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ulib.h>
#include <unistd.h>

#define INSIZE (0x1000000)

char buf[INSIZE];

int main() {
  int FD = open("riscv64_bare.txt", O_RDWR | O_CREAT);
  int len = read(FD, buf, INSIZE);
  int i = 0, begin = 0, end = 0;
  while (i < len) {
    while (buf[i] != ' ') {
      i++;
      end++;
    }
    while (buf[i] == ' ') {
      i++;
    }
    while (buf[i] != '\n') {
      i++;
    }
    if (buf[i - 1] == 'K') {
      char name[end - begin + 1];
      memcpy(name, buf + begin, end - begin);
      name[end - begin] = '\0';
      if (fork() == 0) {
        int returncode = sys_exec(name, 0, NULL);
        if (returncode) {
          cprintf("%s FAILED\n", name);
        } else {
          cprintf("%s OK\n", name);
        }
        exit(0);
      }
    }
    i++;
    begin = i, end = i;
    // while (wait() <= 0) {
    // }
  }
  return 0;
}