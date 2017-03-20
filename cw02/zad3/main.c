#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <zconf.h>
#include <string.h>

int mode=0;

void create_read_lock(int desc) {

    char* line = malloc(50);
    size_t len;

    printf("Podaj nr znaku do zablokowania\n");
    getline(&line, &len, stdin);
    if(line[0] == '\n') getline(&line, &len, stdin);


    int offset = atoi(line);

    printf("%i\n", offset);
    struct flock reader;
    reader.l_type = F_RDLCK;
    reader.l_whence = SEEK_SET;
    reader.l_start=offset;
    reader.l_len=1;
    reader.l_pid=getpid();
    int res;
    if(mode == 1){
       res = fcntl(desc, F_SETLKW, &reader);
    } else {
       res = fcntl(desc, F_SETLK, &reader);
    }
    if(res == 0) printf("Udało się założyć rygiel\n");
    else printf("Nie udało się założyć rygla\n");

    free(line);
}

void create_write_lock(int desc){

    char* line = malloc(50);
    size_t len;

    printf("Podaj nr znaku do zablokowania\n");
    getline(&line, &len, stdin);
    if(line[0] == '\n') getline(&line, &len, stdin);


    int offset = atoi(line);

    struct flock writer;
    writer.l_type = F_WRLCK;
    writer.l_whence = SEEK_SET;
    writer.l_start=offset;
    writer.l_len=1;
    writer.l_pid=getpid();
    int res;
    if(mode == 1){
       res = fcntl(desc, F_SETLKW, &writer);
    } else {
       res = fcntl(desc, F_SETLK, &writer);
    }   
    if(res == 0) printf("Udało się założyć rygiel\n");
    else printf("Nie udało się założyć rygla\n");

    free(line);
}


void print_locks(int desc) {

    printf("\n");

    int file_length = (int) lseek(desc, 0, SEEK_END);

    if (file_length < 0){
        perror("Error finding end of file");
        exit(1);
    }

    for (int i = 0; i < file_length; ++i) {

        struct flock checker;
        checker.l_type = F_WRLCK;
        checker.l_whence = SEEK_SET;
        checker.l_start=i;
        checker.l_len=1;
        checker.l_pid=2;

        int res = fcntl(desc, F_GETLK, &checker);
        if(res < 0){
            perror("Error reading lock");
            exit(4);
        }

        if (checker.l_type == F_RDLCK) printf("Read lock on offset: %i, PID: %i \n", i, checker.l_pid);
        else if (checker.l_type == F_WRLCK) printf("Write lock on offset: %i, PID: %i \n", i, checker.l_pid);


    }
}

void remove_lock(int desc) {
    char* line= malloc(50);
    size_t len;

    printf("Podaj nr znaku odblokowania\n");
    getline(&line, &len, stdin);
    if(line[0] == '\n') getline(&line, &len, stdin);


    int offset = atoi(line);

    struct flock unlocker;
    unlocker.l_type = F_UNLCK;
    unlocker.l_whence = SEEK_SET;
    unlocker.l_start=offset;
    unlocker.l_len=1;
    unlocker.l_pid=getpid();


    int res = fcntl(desc, F_SETLK, &unlocker);
    if(res == 0) printf("Udało się odblokować\n");
    else printf("Nie udało się odblokować\n");

    free(line);
}

void read_char(int desc) {

    char* line = malloc(50);
    size_t len;

    printf("Podaj nr znaku do odczytania\n");
    getline(&line, &len, stdin);
    if(line[0] == '\n') getline(&line, &len, stdin);
    int offset = atoi(line);
    char tmp;

    lseek(desc, offset, SEEK_SET);
    ssize_t result = read(desc,&tmp, 1);

    if(result!=1){
        perror("Error reading char");
    } else {
        printf("Znak to: %c\n",tmp);
    }

    free(line);
}





void replace_char(int desc) {
    char* line = malloc(50);
    size_t len;

    printf("Podaj nr znaku do zmiany\n");

    getline(&line, &len, stdin);
    if(line[0] == '\n') getline(&line, &len, stdin);
    int offset = atoi(line);


    printf("Podaj znak który wpisać do pliku\n");
    getline(&line, &len, stdin);
    if(line[0] == '\n') getline(&line, &len, stdin);
    char tmp = line[0];

    lseek(desc, offset, SEEK_SET);
    ssize_t result = write(desc,&tmp, 1);

    if(result!=1){
        perror("Error writing char");
    } else {
        printf("Udało sie wpisac: %c\n",tmp);
    }
    free(line);
}

int main(int argc, char* argv[]) {



    if(argc < 2){
        printf("%s\n", "bad arguments" );
        exit(2);
    }

    if(argc >=3 && strcmp(argv[2],"-w8")==0){
	mode = 1;
    }


    char* file_name = argv[1];
    int desc = open(file_name, O_RDWR);

    if (desc == 0){
        perror("Error opening file");
        exit(1);
    }


    while (1) {

        printf("Co chcesz zrobic? wpisz:\n");
        printf("1 Ustawienie rygla do odczytu na wybrany znak pliku\n");
        printf("2 Ustawienie rygla do zapisu na wybrany znak pliku\n");
        printf("3 Wyświetlenie listy zaryglowanych znaków pliku \n");
        printf("4 Usuniecie wybranego rygla\n");
        printf("5 Odczyt wybranego znaku pliku,\n");
        printf("6 Zmiana wybranego znaku pliku\n");
        printf("7 Wyjscie z programu\n");

        char tmp = (char) getchar();
        while(tmp == '\n' || tmp == ' ') tmp = (char) getchar();
        switch (tmp){
            case '1':
                create_read_lock(desc);
                break;
            case '2':
                create_write_lock(desc);
                break;
            case '3':
                print_locks(desc);
                break;
            case '4':
                remove_lock(desc);
                break;
            case '5':
                read_char(desc);
                break;
            case '6':
                replace_char(desc);
                break;
            case '7':
                close(desc);
                exit(0);
            default:
                break;
        }
    }


}
