#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(2, "Incorrect usage of command, ex: \"time1 command [args]\"\n");
    exit(1);
  }

  int start = uptime();
  int pid = fork();
  if (pid < 0) {
    fprintf(2, "time1: fork failed\n");
    exit(1);
  }else if (pid == 0) {
    exec(argv[1], &argv[1]);
    fprintf(2, "time1: exec %s failed\n", argv[1]);
    exit(1);
  }else{
    wait(0);
    int end = uptime();
    printf("elapsed time: %d ticks\n", end - start);
    exit(0);
  }
}
