#define _GNU_SOURCE

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <wait.h>

int main (){
  int fd [2];
  int fd2 [2];
  pipe(fd);
  pipe(fd2);


  pid_t forkpid = fork();

  if(forkpid == 0 ){
    close(fd[1]);
    close(fd2[0]);


    char *buff  = (char*) calloc(40, sizeof(char));

    read(fd[0], &buff, 12);
    printf("%s\n", buff);

    const char* add = ">> PIPE";

    strcat(buff, add);

    write(fd2[1], &add, strlen(buff));



  } else {
    close(fd[0]);
    close(fd2[1]);

    char* string = "PIPE >> PIPE";
    char* buff = (char *) calloc(30, sizeof(char));

    write(fd[1], &string, strlen(string));

    read(fd2[0], &buff, 19);

    printf("%s\n", buff );

  }


}
