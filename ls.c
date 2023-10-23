#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>


void parr(char *arr[], int num){
    for(int i=0; i<num; i++){
        printf("%s", arr[i]);
    }
    printf("\t");
}


// l     s    a     r      I    t      R
// list size all reverse inode time recursive
//
// these are the options that i will implement (i hope)
uint8_t options(int argc, char *argv[]){
    int c;
    uint8_t opts = 0;
    uint8_t l = 1, s = 2, a = 4, r = 8, I = 16, t = 32, R = 64;
    while((c = getopt(argc,argv, "lsaritR")) != -1){
        switch (c) {
            case 'l':
                opts += l;
                break;
            case 's':
                opts += s;
                break;
            case 'a':
                opts += a;
                break;
            case 'r':
                opts += r;
                break;
            case 'i':
                opts += I;
                break;
            case 't':
                opts += t;
                break;
            case 'R':
                opts += R;
                break;
                }
    }
    return opts;
}

int main(int argc, char *argv[]) {

    struct stat sb;

    int list, size, reverse, all, inode, time, recursive = 0;
    uint8_t one = 1;
    uint8_t opts = options(argc, argv);

    if((opts & (one << 0)) == 1) list = 1;
    if((opts & (one << 1)) == 2) size = 1;
    if((opts & (one << 2)) == 4) all = 1;
    if((opts & (one << 3)) == 8) reverse = 1;
    if((opts & (one << 4)) == 16) inode = 1;
    if((opts & (one << 5)) == 32) time = 1;
    if((opts & (one << 6)) == 64) recursive = 1;
    /* printf("%d, %d, %d, %d, %d, %d, %d\n", list, size, all, reverse, inode, time, recursive); */

    const char *path = argv[argc-1];
    struct passwd *user;
    struct group *grup;
    char *filepath = malloc (1024);
    DIR *dirp = opendir(path);
    if (dirp == NULL) {
        fprintf(stderr, "Failure on %s: No such file or directory.\n", path);
        exit(0);
    }
    struct dirent *contents = readdir(dirp);
    char *printed[5];
    char *list_str, *inode_str;
    int i;
    int s;
    while (contents != NULL){
        i=0;
        strcpy(filepath, path);
        strcat(filepath, contents->d_name);
        s = stat(filepath, &sb);

        if(inode == 1){
            sprintf(inode_str, "%lu\t", contents->d_ino);
            printed[i] = inode_str;
            i++;
            printf("i is :%d\n", i);
        }
        if(list == 1) {
            user = getpwuid(sb.st_uid);
            grup = getgrgid(sb.st_gid);
            sprintf(list_str, "%d  %s  %s %d %lu\t", sb.st_mode, user->pw_name, grup->gr_name, sb.st_gid, sb.st_size);
            printed[i] = list_str;
            i++;
        }
        if(all == 1) {
            parr(printed, i);
            printf("%s\n", contents->d_name);
        }
        else{
            if (contents->d_name[0] != '.'){
                parr(printed, i);
                printf("%s\n", contents->d_name);
            }
        }
        contents = readdir(dirp);
    }
    closedir(dirp);
    return 0;
}
