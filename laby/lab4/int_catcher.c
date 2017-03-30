#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>


void signal_handler(int signo, siginfo_t *info, void *context ){
  if(signo == SIGUSR1) {
    printf("the number is: %i\n", (*info).si_value.sival_int);
  }
}


int main (){

  struct sigaction act;
  act.sa_sigaction = &signal_handler;
  act.sa_flags = SA_SIGINFO;

  pid_t forkpid = fork();
  if (forkpid == 0){
    if(sigaction(SIGUSR1, &act, NULL) == -1)
      printf("\ncan't catch SIGUSR1\n");
    while(1)
      sleep(1);
  } else {
    while(1){
      sleep(1);
      union sigval value;
      value.sival_int = rand();
      sigqueue(forkpid, SIGUSR1, value);
    }
  }
}
