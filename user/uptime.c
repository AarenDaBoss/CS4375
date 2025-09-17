#include "stdio.h"
#include "user.h"

int main(int argc,char *argv[]){
  int numticks = uptime();
  printf("%d",numticks);
  exit(0);
}
