#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

const int SIZE_OF_ALPHABET = 26;
const char * alphabet = "abcdefghijklmnopqrstuvwxyz";
int adder = 1;


void signal_handler(int signo){
    if(signo == SIGTSTP) {
        adder = -adder;
    }
}

void signal_handler2(int signo){
    if(signo == SIGINT) {
        printf("Odebrano sygnał SIGINT");
        exit(0);
    }
}


int main() {
    printf("Hello, my PID is: %i, feel free to send me some signals\n", getpid());
    int i = 0;

    struct sigaction act;
    act.sa_handler = signal_handler;

    if(sigaction(SIGTSTP, &act, NULL) == -1)
        printf("\ncan't catch SIGUSR1\n");

    if(signal(SIGINT, signal_handler2) == SIG_ERR)
         printf("\ncan't catch SIGINT\n");

    while (1){
        printf("%c \n", alphabet[i]);
        if(i == SIZE_OF_ALPHABET -1 && adder == 1){
            i = 0;
        } else if (i == 0 && adder == -1) {
            i = SIZE_OF_ALPHABET -1;
        } else {
            i += adder;
        }
        sleep(1);
    }
}