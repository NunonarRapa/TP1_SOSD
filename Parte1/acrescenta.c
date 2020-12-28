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

void acrescenta(char const *what, char const *toWhere){
    int fd1, fd2, content;
    char buffer[20];

    fd1 = open(what, O_RDONLY);
    fd2 = open(toWhere, O_WRONLY|O_APPEND, S_IRWXU);
    if (fd1 < 0) { 
        printf("Erro: First file doesnt exist");
        return;
    }
    if (fd2 < 0) {
        printf("Erro: Second file doesnt exist");
        return;
    }

    content = read(fd1, buffer, 20);

    write(fd2, buffer, content);

    while (content > 0) {
        buffer[content] = '\0';

        content = read(fd1, buffer, 20);       

        write(fd2, buffer, content); 
    }

    if (content == -1) {
        perror("Erro: ");
    }

    close(fd1);
    close(fd2);
}

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("\nWrong number of arguments\n");
        exit(EXIT_FAILURE);
    }
    
    acrescenta(argv[1], argv[2]);
    
    return 0;
}