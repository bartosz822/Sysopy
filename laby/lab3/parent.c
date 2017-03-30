#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
  int n = 0;
  if(argc > 1) n = atoi(argv[1]);
  pid_t result=1;
  for (int i = 0; i < n; i++) {
    if(result != 0) result = fork();
  }
  if(result == 0 ) execl("IHello", NULL);
}
