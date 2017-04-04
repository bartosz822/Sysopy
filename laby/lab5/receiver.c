#define _GNU_SOURCE

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <wait.h>

const char* path = "pipe";


int main (){
  FILE* pip = fopen(path, "r");
  if(pip == NULL){
    exit(0);
  }
  char* buff = (char *) calloc(30,sizeof(char));

  fread(buff, 1, 18, pip);
  printf("%s\n", buff );

}
