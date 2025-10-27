// user/task1.c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void)
{
  printf("parent start prio = %d\n", getpriority());
  if (setpriority(17) < 0) {
    printf("setpriority failed\n");
    exit(1);
  }
  printf("parent after set = %d\n", getpriority());

  int pid = fork();
  if (pid < 0) {
    printf("fork failed\n");
    exit(1);
  }
  if (pid == 0) {
    // child should inherit 17
    printf("child inherited prio = %d\n", getpriority());
    // optional: show table if you have ps
    char *argv[] = {"ps", 0};
    exec("ps", argv);
    // it's fine if ps isn't present
    exit(0);
  }
  wait(0);
  exit(0);
}
