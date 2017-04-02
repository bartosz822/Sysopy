//
// Created by bartek on 31.03.17.
//
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>


void signal_handler_child(int signo) {
    if (signo == SIGUSR1) {
        kill(getppid(), SIGRTMIN + (rand() % (SIGRTMAX - SIGRTMIN)));
    } else if (signo == SIGINT) {
        exit(1);
    }

}


int main() {
    printf("I'm a child and my pid is %i \n", getpid());
    srand((unsigned int) getpid());

    sleep((unsigned int) rand() % 10);
    printf("Sending sigusr %i \n", getpid());
    kill(getppid(), SIGUSR1);

    signal(SIGUSR1, signal_handler_child);
    signal(SIGINT, signal_handler_child);

    time_t before_pause;
    time(&before_pause);
    pause();
    printf("I'm unpaused %i \n", getpid());
    time_t after_pause;
    time(&after_pause);
    exit((int) difftime(after_pause, before_pause));
}