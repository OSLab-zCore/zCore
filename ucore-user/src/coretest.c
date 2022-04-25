#include <stdio.h>
#include <ulib.h>

const int max_child = 32;

void sleepy(int pid) {
  int i, time = 1000;
  for (i = 0; i < 10; i++) {
    sleep(time);
    cprintf("I am process %d. Sleep %d x %d slices.\n", pid, i + 1, time);
  }
}

int main(void) {
  int n, pid;
  for (n = 0; n < max_child; n++) {
    if ((pid = fork()) == 0) {
      cprintf("I am child %d\n", n);
      if (n % 2 == 0)
        sleepy(getpid());
      else
        sleep(n * 500);
      cprintf("I am died child %d\n", n);
      exit(0);
    }
    assert(pid > 0);
  }

  if (n > max_child) {
    panic("fork claimed to work %d times!\n", n);
  }

  for (; n > 0; n--) {
    if (wait() <= 0) {
      panic("wait stopped early\n");
    }
  }

  if (wait() > 0) {
    panic("wait got too many\n");
  }

  cprintf("coretest pass.\n");
  return 0;
}