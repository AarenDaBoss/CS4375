#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

static void work(const char *tag, int prio, int loops, int start_delay)
{
  sleep(start_delay);                 // stagger start times
  setpriority(prio);
  for (int i = 0; i < loops; i++) {
    printf("%s tick=%d prio=%d\n", tag, uptime(), prio);
    // small burn
    volatile int s = 0;
    for (int k = 0; k < 300000; k++) s += k;
    // yield a bit
    sleep(1);
  }
  exit(0);
}

int main(void)
{
  // Same priority for A and B, but A becomes RUNNABLE earlier → larger AGE.
  if (fork() == 0) work("A", 40, 5, 0);  // A ready first
  if (fork() == 0) work("B", 40, 5, 3);  // B ready later (smaller age)
  // A different lower priority proc just to show priority still dominates age.
  if (fork() == 0) work("C", 39, 5, 0);

  wait(0); wait(0); wait(0);
  printf("task3 done\n");
  exit(0);
}
