#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <argp.h>

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

    const char *path = "/home/hardal/";
    DIR *dirp = opendir(path);
    struct dirent *contents = readdir(dirp);
    while (contents != NULL){
        if(all)
            printf("%s\n", contents->d_name);
        else{
            if (contents->d_name[0] != '.')
                printf("%s\n", contents->d_name);
        }
        contents = readdir(dirp);
    }
    return 0;
}
