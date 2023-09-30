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
    int i;
    int c;
    uint8_t opts = 0;
    uint8_t l = 1, s = 2, a = 4, r = 8, I = 16, t = 32, R = 64;
    while((c = getopt(argc, argv, "lsaritR") != 0)){
        printf("%d\n", c);
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
            case 'I':
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
    printf("%d\n", c);
    printf("%d\n", opts);
    return opts;
}

int main(int argc, char *argv[]) {
    uint8_t a;
    a = options(argc, argv);
    return 0;
    int hidden, list, size, reverse = 0;
    const char *path = "/data/data/com.termux/files/home/";
    DIR *dirp = opendir(path);
    struct dirent *contents = readdir(dirp);
    while (contents != NULL){
        if(hidden)
            printf("%s\n", contents->d_name);
        else{
            if (contents->d_name[0] != '.')
                printf("%s\n", contents->d_name);
        }
        contents = readdir(dirp);
    }
    return 0;
}
