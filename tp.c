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

    fd = open(file, O_RDONLY);

    if (fd < 0) { 
        perror("Erro: ");
        return;
    }

    content = read(fd, buffer, 20);

    while (content > 0) {
        buffer[content] = '\0';

        printf("%s", buffer);

        content = read(fd, buffer, 20);
    }

    if (content == -1) {
        perror("Erro: ");
    }
    close(fd);
}

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
        count += content;
    }

    if (content == -1) {
        perror("Erro: ");
    }
    close(fd);
    return count;
}

void lista(char const *directory){
    struct stat buf;
    if (lstat(directory, &buf) == -1){ //fills the buf while checking for errors
        perror("lstat");
        exit(EXIT_FAILURE);
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

void acrescenta(char const *file1, char const *file2){
    int fd1, fd2, content;
    char buffer[20];

    fd1 = open(file1, O_RDONLY);
    fd2 = open(file2, O_WRONLY|O_APPEND, S_IRWXU);
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

void informa(char const *file){
    struct stat buf; //will contain the stats of the file
    if (lstat(file, &buf) == -1){ //fills the buf while checking for errors
        perror("lstat");
        exit(EXIT_FAILURE);
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
    char cmd[15], parameters[100], parameters2[100];
    int num, i;
    
    while (1)
    {
        printf("\n%% ");
        scanf("%s", cmd);
        if (strcmp(cmd, "termina") == 0) break; // cmd = termina => terminar o programa de seguida
        else if (strcmp(cmd, "acrescenta") == 0){ scanf("%s", parameters); scanf("%s", parameters2); } //cmd = acrescenta lê 2 parametros
        else scanf("%s", parameters); // qualquer outro cmd lê apenas 1 parametro

        printf("%s %s %s", cmd, parameters, parameters2);
        

        if (strcmp(cmd, "mostra") == 0)
        {
            mostra(parameters);
        }
        else if (strcmp(cmd, "conta") == 0)
        {
            num = conta(parameters);
            if (num >= 0){
                printf("\nO ficheiro contem %d caracteres\n", num);
            }
        }
        else if (strcmp(cmd, "apaga") == 0)
        {
            conta(parameters); // se não existir envia o mesmo erro para o utilizador
            unlink(parameters);
        }
        else if (strcmp(cmd, "informa") == 0)
        {
            informa(parameters);
        }
        else if (strcmp(cmd, "acrescenta") == 0)
        {
            acrescenta(parameters, parameters2);
        }
        else if (strcmp(cmd, "lista") == 0) // FIXME: distinguish directories and files
        {
            lista(parameters);
        }
    }
    return 0;
}