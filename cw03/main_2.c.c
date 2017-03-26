//
// Created by bartek on 25.03.17.
//

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>

int time;
int memory;

void print_usage();

void remove_variable(char *variable_name) {
    if (variable_name[strlen(variable_name) - 1] == '\n') variable_name[strlen(variable_name) - 1] = '\0';
    unsetenv(variable_name);
}

void create_variable(char *variable_name, char *variable_value) {
    if (variable_value[strlen(variable_value - 1) == '\n']) variable_value[strlen(variable_value) - 1] = '\0';
    setenv(variable_name, variable_value, 1);

}

//assuming max 5 args
void execute(char *command) {
    char **argv = calloc(6, sizeof(char *));
    argv[0] = strtok(command, " ");
    int i = 1;
    while (i < 5 && (argv[i] = strtok(NULL, " ")) != NULL)(i++);
    if (argv[i - 1][strlen(argv[i - 1]) - 1] == '\n') argv[i - 1][strlen(argv[i - 1]) - 1] = '\0';
    argv[i] = NULL;
    pid_t forkpid = fork();
    if (forkpid == 0) {
        struct rlimit limits_cpu;
        limits_cpu.rlim_cur = (rlim_t) time;
        limits_cpu.rlim_max = (rlim_t) time;
        setrlimit(RLIMIT_CPU, &limits_cpu);
        struct rlimit limits_memory;
        limits_memory.rlim_cur = (rlim_t) memory;
        limits_memory.rlim_max = (rlim_t) memory;
        setrlimit(RLIMIT_AS, &limits_memory);
        execvp(argv[0], argv);
        exit(0);
    } else {
        int status;
        waitpid(-1, &status, 0);
        if (!WIFEXITED(status)) {
            printf("Child process exited with error on command: %s \n", command);
            print_usage();
            exit(1);
        }
        print_usage();
    }

    free(argv);
}

void print_usage() {
    struct rusage childusage;
    getrusage(RUSAGE_CHILDREN, &childusage);
    printf("user cpu : %ld us || system cpu : %ld us || maxrss : %ld bytes|| ixrss : %ld bytes || idrss : %ld bytes || isrss : %ld bytes",
           childusage.ru_utime.tv_usec, childusage.ru_stime.tv_usec, childusage.ru_maxrss, childusage.ru_ixrss,
           childusage.ru_idrss, childusage.ru_idrss);
}

void parse_line(char *line) {
    if (line[0] == '#') {
        char *variable_name = strtok(line, " ");
        char *variable_value = strtok(NULL, " ");
        if (variable_value == NULL) {
            remove_variable(variable_name + 1);
        } else {
            create_variable(variable_name + 1, variable_value);
        }

    } else {
        execute(line);
    }
}

void read_file(char *file_path) {
    FILE *file;
    file = fopen(file_path, "r");


    if (file == NULL) {
        perror("Error while opening the file!");
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;


    while ((read = getline(&line, &len, file)) != -1) {
        if (read >= 1) parse_line(line);
    }

    fclose(file);


}


int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Bad arguments");
        exit(EXIT_FAILURE);
    }
    time = atoi(argv[2]);
    memory = atoi(argv[3]);
    char *file_path = argv[1];
    read_file(file_path);

    return 0;
}