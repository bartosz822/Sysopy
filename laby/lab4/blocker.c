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

  // struct sigaction act;
  // act.sa_handler = signal_handler;

  pid_t forkpid = fork();
  if (forkpid == 0){
    sigset_t set;
    sigemptyset(&set);
    sigfillset(&set);
    sigprocmask(SIG_BLOCK, &set, NULL);
    while(1){
      sleep(1);
      printf("%s\n", "nadal dzialam" );
    }
  } else {
    int z = 0;
    while(1){
      sleep(1);
      z++;
      kill(forkpid,SIGUSR1);
      kill(forkpid,SIGUSR2);
      kill(forkpid,SIGABRT);
      if(z%5 == 0) kill(forkpid,SIGKILL);
    }
  }
}
