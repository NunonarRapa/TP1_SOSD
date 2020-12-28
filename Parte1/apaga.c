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


int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("\nWrong number of arguments\n");
        exit(EXIT_FAILURE);
    }
    unlink(argv[1]);
    
    return 0;
}