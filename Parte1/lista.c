#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdint.h>

void lista(char const *directory){
    struct stat buf;
    DIR *dir;
    struct dirent *lsdir;
    if (lstat(directory, &buf) == -1){ //fills the buf while checking for errors
        perror("lstat");
        return;
    }
    switch (buf.st_mode & S_IFMT) { //switch case to see if its a directory
        case S_IFBLK: printf("\nThats a block device, please give a directory as an argument"); return;
        case S_IFCHR: printf("\nThats a character device, please give a directory as an argument"); return;
        case S_IFDIR: break; // keep function going
        case S_IFIFO: printf("\nThats a FIFO/pipe, please give a directory as an argument"); return;
        case S_IFLNK: printf("\nThats a symlink, please give a directory as an argument"); return;
        case S_IFREG: printf("\nThats a regular file, please give a directory as an argument"); return;
        case S_IFSOCK: printf("\nThats a socket, please give a directory as an argument"); return;
        default: printf("\nThats a unknown file type, please give a directory as an argument"); return;
    }
    
    dir = opendir(directory);
    
    while (( lsdir = readdir(dir)) != NULL )
    {
        if (strcmp(lsdir->d_name, ".") == 0 | strcmp(lsdir->d_name, "..") == 0) {}
        else printf ("%s\n", lsdir->d_name);
    }

    closedir(dir);
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("\nWrong number of arguments\n");
        exit(EXIT_FAILURE);
    }

    lista(argv[1]);
    
    return 0;
}