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

int conta(char const *file){
    int fd, content, count = 0;
    char buffer[21];

    fd = open(file, O_RDONLY);

    if (fd < 0) { 
        perror("Erro: ");
        return -1;
    }

    content = read(fd, buffer, 20);
    count = content;

    while (content > 0) {
        buffer[content] = '\0';

        content = read(fd, buffer, 20); 
        count += content; //conta todos as letras, espaços, \n's, etc...
    }

    if (content == -1) {
        perror("Erro: ");
    }
    close(fd);
    return count;
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("\nWrong number of arguments\n");
        exit(EXIT_FAILURE);
    }
    
    conta(argv[1]);
    
    return 0;
}