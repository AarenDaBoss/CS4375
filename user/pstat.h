#define UNUSED   0
#define SLEEPING 1
#define RUNNABLE 2
#define RUNNING  3
#define ZOMBIE   4

struct pstat {
  int  pid;
  int  state;
  uint size;
  int  ppid;
  char name[16];
  int  priority;
  uint readytime;
};
