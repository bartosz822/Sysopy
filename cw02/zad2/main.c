#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>


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


void search(char *current_path, int size) {

    DIR *dir;
    struct dirent *dr;
    struct stat file;

    dir = opendir(current_path);

    if (dir == NULL) return;

    while ((dr = readdir(dir)) != NULL) {
        char *new_path = malloc((strlen(current_path) + strlen(dr->d_name) + 2) * sizeof(char));
        strcpy(new_path, current_path);
        if (current_path[strlen(current_path) - 1] != '/') strcat(new_path, "/");
        strcat(new_path, dr->d_name);

        if (dr->d_type == DT_DIR && strcmp(dr->d_name, "..") != 0 && strcmp(dr->d_name, ".") != 0) {
            search(new_path, size);
        } else if (dr->d_type == DT_REG || DT_UNKNOWN) {
            int result = lstat(new_path, &file);
            if (result < 0) error();
            if (S_ISDIR(file.st_mode)) {
                search(current_path, size);
            } else if (S_ISREG(file.st_mode) && file.st_size <= size) {
                print_info(&file, new_path);
            }
        }
        free(new_path);
    }


}


int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Bad arguments number");
        exit(EXIT_FAILURE);
    }

    char root[PATH_MAX + 1];
    size = atoi(argv[2]);

    realpath(argv[1], root);
    search(root, size);

    return 0;
}
