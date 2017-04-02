//
// Created by bartek on 31.03.17.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <wait.h>
#include <time.h>

int counter;
pid_t child;

void child_handler(int signo) {
    if (signo == SIGUSR1) {
        counter++;
        kill(getppid(), SIGUSR1);
    } else if (signo == SIGUSR2) {
        printf("I'm a child and I've just received SIGUSR2, I've sent %i SIGUSR1 signals, now I'm exiting\n", counter);
        exit(0);
    } else if (signo == SIGINT) {
        exit(1);
    } else if (signo == SIGRTMIN) {
        counter++;
        kill(getppid(), SIGUSR1);
    } else if (signo == SIGRTMIN + 1) {
        printf("I'm a child and I've just received SIGRTMIN+1, I've sent %i SIGUSR1 signals, now I'm exiting\n",
               counter);
        exit(0);
    }

}

void parent_handler(int signo) {

    if (signo == SIGUSR1) {
        counter++;
    } else if (signo == SIGINT) {
        kill(child, SIGINT);
        exit(1);
    }
}


void child_actions() {

    signal(SIGUSR1, child_handler);
    signal(SIGUSR2, child_handler);
    signal(SIGINT, child_handler);
    signal(SIGRTMIN, child_handler);
    signal(SIGRTMIN + 1, child_handler);


    while (1)
        pause();

}

void parent_actions(pid_t child, int l, int *children, int n, int time) {

    int type = rand() % 3 + 1;

    signal(SIGUSR1, parent_handler);
    signal(SIGINT, parent_handler);

    union sigval value;

    for (int i = 0; i < l; ++i) {
        printf("Sending SIGUSR1 nr %i to my child\n", i);
        if (type == 1) {
            kill(children[rand() % n], SIGUSR1);
        } else if (type == 2) {
            sigqueue(children[rand() % n], SIGUSR1, value);
        } else {
            kill(children[rand() % n], SIGRTMIN);
        }
        sleep((unsigned int) time);
    }

    for (int j = 0; j < n; ++j) {
        kill(children[j], SIGUSR2);
        wait(NULL);
    }



    while (wait(NULL)) {
        if (errno == ECHILD) {
            break;
        }
    }

    printf("I've send %i SIGUSR1 signals, and received back %i signals\n", l, counter);
    free(children);

}

int main(int argc, char **argv) {

    srand(time(NULL));

    if (argc < 3 || argc > 4) {
        printf("Bad arguments\n");
        exit(2);
    }

    int time;
    if (argc == 4) {
        time = atoi(argv[3]);
    } else
        time = 0;


    int n = atoi(argv[1]);
    int l = atoi(argv[2]);
    counter = 0;

    int *children = calloc((size_t) n, sizeof(int));

    pid_t forkpid = 1;
    for (int i = 0; i < n; ++i) {
        if (forkpid != 0) {
            forkpid = fork();
            children[i] = forkpid;
        }
    }

    if (forkpid == 0) {
        child_actions();
    } else {
        child = forkpid;
        parent_actions(forkpid, l, children, n, time);
    }


    return 0;
}