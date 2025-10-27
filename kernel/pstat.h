// kernel/pstat.h
#ifndef PSTAT_H
#define PSTAT_H
#include "types.h"

struct pstat {
  int  pid;         // process id
  int  state;       // enum procstate
  uint size;        // memory size (bytes)
  int  ppid;        // parent pid (0 if none)
  char name[16];    // process name

  // NEW for HW3 Task 1/3:
  int  priority;    // base priority (0..49)
  uint readytime;   // tick when it became RUNNABLE (for age)
};

#endif
