#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/pstat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {

  int start = uptime();
  int pid = fork();
  struct rusage ru;


  if (argc < 2) {
    fprintf(2, "Incorrect usage of command, ex: \"time1 command [args]\"\n");
    exit(1);
  }

  if (pid < 0) {
    fprintf(2, "time1: fork failed\n"); //fork failed
    exit(1);
  }else if (pid == 0) { //this is the child branch/new process
    exec(argv[1], &argv[1]);
    fprintf(2, "time1: exec %s failed\n", argv[1]);
    exit(1);
  }else{//this is the parent branch/original process
    if (wait2(0, &ru) < 0) {
      fprintf(2, "time1: wait2 failed\n");
      exit(1);
    }
}

int end = uptime();
int elapsed = end - start;
int cpu = ru.cputime;
int percent = (elapsed > 0) ? (cpu * 100 / elapsed) : 0;

printf("elapsed time: %d ticks , cpu time: %d ticks , %d%% CPU\n",
       elapsed, cpu, percent);
}

