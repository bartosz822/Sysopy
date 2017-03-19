//
// Created by bartek on 18.03.17.
//
#define _XOPEN_SOURCE 500

#include <ftw.h>
#include <fftw3.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>


int size;

char *get_permissions(struct stat file) {
    char *perms = calloc(10, sizeof(char));
    perms[0] = (char) (S_ISDIR(file.st_mode) ? 'd' : '-');
    perms[1] = (char) ((S_IRUSR & file.st_mode) ? 'r' : '-');
    perms[2] = (char) ((file.st_mode & S_IWUSR) ? 'w' : '-');
    perms[3] = (char) ((file.st_mode & S_IXUSR) ? 'x' : '-');
    perms[4] = (char) ((file.st_mode & S_IRGRP) ? 'r' : '-');
    perms[5] = (char) ((file.st_mode & S_IWGRP) ? 'w' : '-');
    perms[6] = (char) ((file.st_mode & S_IXGRP) ? 'x' : '-');
    perms[7] = (char) ((file.st_mode & S_IROTH) ? 'r' : '-');
    perms[8] = (char) ((file.st_mode & S_IWOTH) ? 'w' : '-');
    perms[9] = (char) ((file.st_mode & S_IXOTH) ? 'x' : '-');
    return perms;
}

void print_info(const struct stat *file, const char *new_path) {
    char date[10];
    char *perms;
    strftime(date, 10, "%d-%m-%y", localtime(&((*file).st_ctime)));
    printf("%s %i %s %s \n", new_path, (int) (*file).st_size, perms = get_permissions((*file)), date);
    free(perms);
}

void error() {
    printf("Error occured");
    exit(EXIT_FAILURE);
}

int info_printer(const char *fpath, const struct stat *file, int tflag, struct FTW *ftwbuf) {
    if(tflag == FTW_F && file->st_size < size){
        print_info( file, fpath);
    }
    return 0;
}


void search_nftw(char *current_path) {
    int result = nftw(current_path, info_printer,20, FTW_PHYS);
}


int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Bad arguments number");
        exit(EXIT_FAILURE);
    }

    char root[PATH_MAX + 1];
    size = atoi(argv[2]);

    realpath(argv[1], root);
    search_nftw(root);

    return 0;
}