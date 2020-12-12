#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void mostra(char const *file){
    int fd, content;
    char buffer[21];

    fd = open(file, O_RDONLY);

    if (fd < 0) { 
        perror("Erro na abertura do ficheiro");
        return;
    }

    // ficheiro disponivel no descritor fd
    content = read(fd, buffer, 20);

    while (content > 0) {
        buffer[content] = '\0';

        printf("%s", buffer);

        content = read( fd, buffer, 20);
    }

    // -1 houve erro
    if (content == -1) {
        perror("Erro no content do ficheiro");
    }
    close(fd);
}

int conta(char const *file){
    int fd, content, count = 0;
    char buffer[21];

    fd = open(file, O_RDONLY);

    if (fd < 0) { 
        perror("Erro na abertura do ficheiro");
        return;
    }

    // ficheiro disponivel no descritor fd
    content = read(fd, buffer, 20);
    count = content;

    while (content > 0) {
        buffer[content] = '\0';

        printf("%s", buffer);

        content = read( fd, buffer, 20);
        count += content;
    }

    // -1 houve erro
    if (content == -1) {
        perror("Erro no content do ficheiro");
    }
    close(fd);
    return count;
}

void lista(char const *directory)
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
    char cmd[10];
    int num;
    
    do
    {
        printf("\n%%");
        scanf("%s", cmd);
        
        if (strcmp(cmd, "mostra") == 0)
        {
            mostra(argv[1]); // FIXME: file given when written mostra
        }
        else if (strcmp(cmd, "conta") == 0)
        {
            num = conta(argv[1]); // FIXME: file given when written conta
            printf("%d", num);
        }
        else if (strcmp(cmd, "apaga") == 0)
        {
            
        }
        else if (strcmp(cmd, "informa") == 0)
        {
            
        }
        else if (strcmp(cmd, "acrescenta") == 0)
        {
            
        }
        else if (strcmp(cmd, "lista") == 0) // FIXME: distinguish directories and files
        {
            lista(argv[1]); // FIXME: path given when written lista
        }
        

    } while (strcmp(cmd, "termina") != 0);
    
    return 0;
}