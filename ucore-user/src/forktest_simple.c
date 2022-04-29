#include <stdio.h>
#include <ulib.h>

const int max_child = 3;

int main(void) {
  int n, pid;
  for (n = 0; n < max_child; n++) {
    if ((pid = fork()) == 0) {
      cprintf("I am child %d\n", n);
      exit(0);
    }
    assert(pid > 0);
  }

  if (n > max_child) {
    panic("fork claimed to work %d times!\n", n);
  }

  for (; n > 0; n--) {
    while (wait() <= 0) {
    }
  }

  cprintf("forktest pass.\n");
  return 0;
}