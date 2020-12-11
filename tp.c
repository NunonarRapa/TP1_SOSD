#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void MyWayLS(char const *directory)
{
    DIR *dir;
    struct dirent *lsdir;

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
    MyWayLS(argv[1]);
    
    return 0;
}