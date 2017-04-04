#define _GNU_SOURCE

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>

const char* path = "pipe";

int main (){
  mkfifo(path, 0666);
  FILE* pip = fopen(path, "w");
  char* message = "TOP SECRET MESSAGE";

  fwrite(message, 1, strlen(message), pip);

  unlink(path);

  exit(0);


}
