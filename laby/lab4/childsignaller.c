#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int signals = 0;

void signal_handler(int signo){
  if(signo == SIGUSR1) {
    signals++;
    printf("signal nr: %i\n", signals);
  }
}


int main (){

  struct sigaction act;
  act.sa_handler = signal_handler;

  pid_t forkpid = fork();
  if (forkpid == 0){
    if(sigaction(SIGUSR1, &act, NULL) == -1)
      printf("\ncan't catch SIGUSR1\n");
    while(1)
      sleep(1);
  } else {
    while(1){
      sleep(1);
      kill(forkpid,SIGUSR1);
    }
  }
}
