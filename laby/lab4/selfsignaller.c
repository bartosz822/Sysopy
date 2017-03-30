#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>


void signal_handler(int signo){
  if(signo == SIGUSR1) printf("%s\n", "ja cie ale sygnał");

}


int main (){

  struct sigaction act;
  act.sa_handler = signal_handler;


  if (sigaction(SIGUSR1, &act, NULL) == -1)
    printf("\ncan't catch SIGUSR1\n");

  raise(SIGUSR1);


}
