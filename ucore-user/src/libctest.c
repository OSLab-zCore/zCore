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
  read(FD, buf, INSIZE);
  for (int i = 0; i < 10; i++) cprintf("");
  return 0;
}