//#include "stdio.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char *argv[]){
  fprintf(1,"Up %d clock ticks\n",uptime());
  exit(0);
}
