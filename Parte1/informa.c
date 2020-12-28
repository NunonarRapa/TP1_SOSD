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

void informa(char const *file){
    struct stat buf; //will contain the stats of the file
    if (lstat(file, &buf) == -1){ //fills the buf while checking for errors
        perror("lstat");
        return;
    }
    printf("\nFile type: ");
    switch (buf.st_mode & S_IFMT) { //switch case to see the type of the file | man lstat
        case S_IFBLK:  printf("Block Device\n");            break;
        case S_IFCHR:  printf("Character Device\n");        break;
        case S_IFDIR:  printf("Directory\n");               break;
        case S_IFIFO:  printf("FIFO/pipe\n");               break;
        case S_IFLNK:  printf("Symlink\n");                 break;
        case S_IFREG:  printf("Regular File\n");            break;
        case S_IFSOCK: printf("Socket\n");                  break;
        default:       printf("Unknown?\n");                break;
    }
    printf("I-node number:            %ju\n", (uintmax_t) buf.st_ino);
    printf("Ownership:                UID=%ju\n", (uintmax_t) buf.st_uid);
    printf("File size:                %jd bytes\n", (intmax_t) buf.st_size);
    printf("Last status change:       %s", ctime(&buf.st_ctime));
    printf("Last file access:         %s", ctime(&buf.st_atime));
    printf("Last file modification:   %s", ctime(&buf.st_mtime));
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("\nWrong number of arguments\n");
        exit(EXIT_FAILURE);
    }
    
    informa(argv[1]);
    
    return 0;
}