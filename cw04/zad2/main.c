#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int N;
int M;
int counter;
int pids_in_array;
int *asked_for_continue_pids;
int *children;
int ended;

int in_pid_array(int *array, int x) {
    for (int i = 0; i < sizeof(array) / sizeof(array[0]); ++i) {
        if (x == array[i]) return 1;
    }
    return 0;
}

void add_to_pid_array(int *array, int x) {
    array[pids_in_array++] = x;
}

void signal_handler_parent(int signo, siginfo_t *info, void *context) {
    if (signo == SIGUSR1) {
        printf("I've just caught SIGUSR1 from  %i\n", (*info).si_pid);
        if (!in_pid_array(asked_for_continue_pids, (*info).si_pid))
            add_to_pid_array(asked_for_continue_pids, (*info).si_pid);
        if (counter == M) {
            kill((*info).si_pid, SIGUSR1);
        } else {
            counter++;
            if (counter == M) {
                for (int i = 0; i < pids_in_array; ++i) {
                    kill(asked_for_continue_pids[i], SIGUSR1);
                    waitpid(asked_for_continue_pids[i], NULL, 0);
                }
            }

        }
    } else if (signo == SIGINT) {
        for (int i = 0; i < N; ++i) {
            kill(children[i], SIGINT);
        }
        exit(1);
    } else if (signo == SIGCHLD) {
        printf("Process : %i ended with code %i \n", (*info).si_pid, (*info).si_status);
        ended++;
    } else if (signo >= SIGRTMIN && signo <= SIGRTMAX) {
        printf("I've received signal: SIGMIN+%i \n", signo - SIGRTMIN);
    }
}

void parent_actions() {

    struct sigaction act;
    act.sa_sigaction = &signal_handler_parent;
    act.sa_flags = SA_SIGINFO;
    sigemptyset(&act.sa_mask);


    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGCHLD, &act, NULL);
    for (int i = SIGRTMIN; i <= SIGRTMAX; i++) {
        sigaction(i, &act, NULL);
    }

    while (wait(NULL)) {
        if (errno == ECHILD) {
            break;
        }
    }
}

int main(int argc, char **argv) {


    if (argc != 3) {
        printf("Bad arguments\n");
        exit(2);
    }

    counter = 0;
    pids_in_array = 0;

    N = atoi(argv[1]);
    M = atoi(argv[2]);
    ended = 0;

    asked_for_continue_pids = calloc((size_t) N, sizeof(int *));
    children = calloc((size_t) N, sizeof(int *));


    int forkpid = 1;
    for (int i = 0; i < N; ++i) {
        if (forkpid != 0) {
            forkpid = fork();
            children[i] = forkpid;
        }

    }
    if (forkpid == 0) {
        execle("./child", NULL);
    } else {
        parent_actions();
    }


    return 0;
}