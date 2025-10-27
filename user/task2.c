#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

static void burn(const char *tag, int prio, int loops)
{
  if (setpriority(prio) < 0) {
    printf("%s: setpriority(%d) failed\n", tag, prio);
    exit(1);
  }
  for (int i = 0; i < loops; i++) {
    // do some work to hold CPU a bit
    volatile int s = 0;
    for (int k = 0; k < 500000; k++) s += k;
    printf("%s tick=%d prio=%d\n", tag, uptime(), prio);
    // brief sleep so outputs interleave predictably
    sleep(1);
  }
  exit(0);
}

int main(void)
{
  // Child A: prio 40
  int a = fork();
  if (a == 0) burn("A", 40, 5);

  // Child B: prio 39
  int b = fork();
  if (b == 0) burn("B", 39, 5);

  // Let A/B start first
  sleep(1);

  // Child C: prio 40 (same as A) starts a bit later
  int c = fork();
  if (c == 0) burn("C", 40, 5);

  // Parent waits
  wait(0); wait(0); wait(0);
  printf("task2 done\n");
  exit(0);
}
