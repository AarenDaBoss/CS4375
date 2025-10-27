#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"  // NPROC
#include "user/user.h"
#include "pstat.h"

static const char *stname(int st) {
  switch (st) {
    case UNUSED:   return "unused";
    case SLEEPING: return "sleeping";
    case RUNNABLE: return "runnable";
    case RUNNING:  return "running";
    case ZOMBIE:   return "zombie";
    default:       return "unknown";
  }
}

int
main(int argc, char **argv)
{
  struct pstat procs[NPROC];
  int n = getprocs(procs);
  if (n < 0) {
    printf("ps: getprocs failed\n");
    exit(1);
  }

  printf("pid   state      size   ppid   priority   age   name\n");

  int now = uptime();
  for (int i = 0; i < n; i++) {
    int st = procs[i].state;
    int age = (st == RUNNABLE && now >= (int)procs[i].readytime)
                ? (now - (int)procs[i].readytime)
                : -1;

    // build state column padded to ~10 with spaces
    const char *s = stname(st);
    char spad[12];
    int k = 0;
    for (; s[k] && k < 10; k++) spad[k] = s[k];
    while (k < 10) spad[k++] = ' ';
    spad[k] = 0;

    // print using only %d and %s (no widths)
    printf("%d   %s  %d   %d     %d        ",
           procs[i].pid, spad,
           (int)procs[i].size,
           procs[i].ppid,
           procs[i].priority);

    if (age >= 0) printf("%d   ", age);
    else          printf("N/A  ");

    printf("%s\n", procs[i].name);
  }
  exit(0);
}
