#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

static void busy(const char *tag, int prio, int loops, int log_every)
{
  if (setpriority(prio) < 0) {
    printf("%s: setpriority(%d) failed\n", tag, prio);
    exit(1);
  }

  int first_tick = -1;
  for (int i = 0; i < loops; i++) {
    // burn CPU
    volatile int s = 0;
    for (int k = 0; k < 400000; k++) s += k;

    if (first_tick < 0) first_tick = uptime();
    if (log_every && (i % log_every) == 0) {
      printf("%s tick=%d prio=%d\n", tag, uptime(), prio);
    }
  }
  printf("%s done at tick=%d\n", tag, uptime());
  exit(0);
}

int main(void)
{
  // LOW starts first with low base prio; HIGH starts soon after with higher base.
  // With aging ON, LOW will eventually catch up and run despite HIGH.
  int pid;

  if ((pid = fork()) == 0) {
    // LOW: very low base priority; lots of loops, log occasionally
    busy("LOW ", 10, 120, 20);
  }

  sleep(5); // let LOW sit RUNNABLE to accumulate AGE before HIGH arrives

  if ((pid = fork()) == 0) {
    // HIGH: higher base priority; runs a lot initially
    busy("HIGH", 30, 120, 20);
  }

  wait(0); wait(0);
  printf("task4 done\n");
  exit(0);
}
