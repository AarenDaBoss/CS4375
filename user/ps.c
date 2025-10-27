#include "kernel/param.h"
#include "kernel/types.h"
#include "user/user.h"
#include "user/pstat.h"

int
main(int argc, char **argv)
{
  struct pstat uproc[NPROC];
  int nprocs;
  int i;

  static const char *states[] = {
    [UNUSED]   "unused  ",
    [SLEEPING] "sleeping",
    [RUNNABLE] "runnable",
    [RUNNING]  "running ",
    [ZOMBIE]   "zombie  "
  };

  // get array of per-proc structs; kernel returns count
  nprocs = getprocs(uproc);
  if (nprocs < 0)
    exit(-1);

  // current time in ticks to compute age
  uint now = uptime();

  printf("pid\tstate\t\tsize\tppid\tpriority\tage\tname\n");
  for (i = 0; i < nprocs; i++) {
    int st = uproc[i].state;
    const char *sname = (st >= 0 && st <= ZOMBIE) ? states[st] : "unknown";
    printf("%d\t%s\t%u\t%d\t%d\t\t",
           uproc[i].pid, sname, uproc[i].size, uproc[i].ppid, uproc[i].priority);

    if (st == RUNNABLE) {
      uint age = (now >= uproc[i].readytime) ? (now - uproc[i].readytime) : 0;
      printf("%u\t", age);
    } else {
      printf("N/A\t");
    }

    printf("%s\n", uproc[i].name);
  }

  exit(0);
}
