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

void mostra(char const *file){
    int fd, content;
    char buffer[21];

    fd = open(file, O_RDONLY); //abre em read only pois so queremos mostrar o texto

    if (fd < 0) { //caso nao consiga abrir o ficheiro
        perror("Erro: ");
        return;
    }

    content = read(fd, buffer, 20);

    printf("\n");

    while (content > 0) {
        buffer[content] = '\0';

        printf("%s", buffer); //vai escrevendo o ficheiro para a consola

        content = read(fd, buffer, 20);
    }

    if (content == -1) {
        perror("Erro: ");
    }
    close(fd); //fecha o ficheiro
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("\nWrong number of arguments\n");
        exit(EXIT_FAILURE);
    }
    
    mostra(argv[1]);
    
    return 0;
}