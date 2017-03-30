#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
  char* x = "abcd";
  int x2 = 1;
  float x3 = 3.14;

  int n = 1;
  if(argc > 1) n = atoi(argv[1]);
  pid_t result=1;
  for (int i = 0; i < n; i++) {
    if(result != 0) result = fork();
  }
  if(result != 0) wait();
  if(result == 0 ) {
    printf("child %s %i %f\n", x, x2, x3 );
    x = "iksde";
    x2 = 2;
    x3 += -1.0;
    printf("child %s %i %f\n", x, x2, x3 );
  }

  if(result != 0) printf("parent %s %i %f\n", x, x2, x3 );

}
