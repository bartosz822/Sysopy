#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>



int main(int argc, char* argv []){


  printf("%s\n", "co chcesz zrobić ?\nwpisz a - założenie locka do odczytu \nb - założenie locka do zapisu ");
  char tmp = getchar();
  printf("%c\n", tmp );
  if(tmp == 'a'){
    int desc = open("testfile", O_RDONLY);
    struct flock reader;
    reader.l_type = 0;
    reader.l_whence = 0;
    reader.l_start=0;
    reader.l_len=0;
    reader.l_pid=getpid();
    int res = fcntl(desc, F_SETLK, &reader);
    if(res == 0) {
      printf("%s\n", "udało sie dostac locka" );
      printf("odblokowac ? y\n");
      tmp = getchar();
      while ( tmp != 'y'){
      tmp = getchar();
      }
      reader.l_type=F_UNLCK;
      fcntl(desc, F_SETLK, &reader);
    }
    else printf("%s\n", "nie udałosie dostac locka" );

  } else if(tmp == 'b') {
    int desc = open("testfile", O_WRONLY);
    struct flock writer;
    writer.l_type = F_WRLCK;
    writer.l_whence = 0;
    writer.l_start=0;
    writer.l_len=0;
    writer.l_pid=getpid();

    int res = fcntl(desc, F_SETLK, &writer);

    if(res == 0) {
      printf("%s\n", "udało sie dostac locka" );
      printf("odblokowac ? y\n");
      tmp = getchar();
      while (tmp != 'y' ){
        tmp = getchar();
      }
      writer.l_type=F_UNLCK;
      fcntl(desc, F_SETLK, &writer);
    }
    else printf("%s\n", "nie udałosie dostac locka" );
  } else {
    printf("%s\n", "takiej opcji nie ma");
  }
}
