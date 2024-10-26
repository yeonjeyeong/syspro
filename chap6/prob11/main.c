#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*, int, int, int);

int main(int argc, char **argv) {
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ+1];
    int showInode = 0, showPath = 0, quoteNames = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            showInode = 1;
        } else if (strcmp(argv[i], "-p") == 0) {
            showPath = 1;
        } else if (strcmp(argv[i], "-Q") == 0) {
            quoteNames = 1;
        } else {
            dir = argv[i];
        }
    }

    if (!dir) dir = ".";

    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(1);
    }

    while ((d = readdir(dp)) != NULL) {
        sprintf(path, "%s/%s", dir, d->d_name);
        if (lstat(path, &st) < 0)
            perror(path);
        else 
            printStat(path, d->d_name, &st, showInode, showPath, quoteNames);
    }

    closedir(dp);
    exit(0);
}

void printStat(char *pathname, char *file, struct stat *st, int showInode, int showPath, int quoteNames) {
    if (showInode)
        printf("%10ld ", st->st_ino);

    printf("%5ld ", st->st_blocks);
    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3ld ", st->st_nlink);
    printf("%s %s ", getpwuid(st->st_uid)->pw_name,
           getgrgid(st->st_gid)->gr_name);
    printf("%9ld ", st->st_size);
    printf("%.12s ", ctime(&st->st_mtime)+4);

    if (quoteNames)
        printf("\"%s\"\n", file);
    else
        printf("%s\n", file);

    if (showPath)
        printf(" %s\n", pathname);
}

char type(mode_t mode) {
    if (S_ISREG(mode))
        return('-');
    if (S_ISDIR(mode))
        return('d');
    if (S_ISCHR(mode))
        return('c');
    if (S_ISBLK(mode))
        return('b');
    if (S_ISLNK(mode))
        return('l');
    if (S_ISFIFO(mode))
        return('p');
    if (S_ISSOCK(mode))
        return('s');
}

char* perm(mode_t mode) {
    static char perms[10];
    
    strcpy(perms, "---------");
    
    perms[0] = mode & S_IRUSR ? 'r' : '-';
    perms[1] = mode & S_IWUSR ? 'w' : '-';
    perms[2] = mode & S_IXUSR ? 'x' : '-';
    
    perms[3] = mode & S_IRGRP ? 'r' : '-';
    perms[4] = mode & S_IWGRP ? 'w' : '-';
    perms[5] = mode & S_IXGRP ? 'x' : '-';
    
    perms[6] = mode & S_IROTH ? 'r' : '-';
    perms[7] = mode & S_IWOTH ? 'w' : '-';
    perms[8] = mode & S_IXOTH ? 'x' : '-';
    
    return(perms);
}

