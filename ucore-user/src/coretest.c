#include <stdio.h>
#include <time.h>
#include <ulib.h>

const int max_child = 32;

void sleepy_print(int pid) {
  struct timespec time = {.tv_sec = 0, .tv_nsec = 1e9};
  for (int i = 0; i < 10; i++) {
    sleep(&time);
    cprintf("I am process %d. Sleep %d x %d slices.\n", pid, i + 1, time);
  }
}

void sleepy(int n, int pid) {
  long int tv_nsec = n * 5e8;
  cprintf("I am process %d. Sleep %ld nsec.\n", pid, tv_nsec);
  struct timespec time = {.tv_sec = 0, .tv_nsec = 5e8};
  for (int i = 0; i < n; i++) sleep(&time);
}

int main(void) {
  int start = sys_times();

  int n, pid;
  for (n = 0; n < max_child; n++) {
    if ((pid = fork()) == 0) {
      cprintf("I am child %d.\n", n);
      if (n % 2 == 0)
        sleepy_print(getpid());
      else
        sleepy(n, getpid());
      cprintf("I am died child %d.\n", n);
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

  int end = sys_times();
  cprintf("coretest pass. time_delta = %d.\n", end - start);
  return 0;
}