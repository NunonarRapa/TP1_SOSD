#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFSIZE 20
#define LINESIZE 60
#define DELIM " \n"
int MySystem (char* cmd, char* args[]){

  	int retstatus;
	pid_t pid;
	

	pid = fork(); // Criar processo filho 
	
	if ( pid == -1) {
		perror("Erro no fork");
		exit(EXIT_FAILURE);
	}

	if ( pid == 0){ //Filho
		execvp(cmd, args); // Executa o comando no processo filho, permitindo que o programa continue 
		perror("Erro no exec");
		exit(EXIT_FAILURE);
	}

	wait(&retstatus); // Esperar que o processo filho termine
	return WEXITSTATUS(retstatus);
}

char **Args(char *line){
	int pos = 0;
	char *token;
	char **args = (char **) malloc(BUFSIZE * sizeof(char *));

	token = strtok(line, DELIM); // Separar a string completa através da função strtok
	while(token != NULL){
		args[pos] = token;
		pos++;

		token = strtok(NULL, DELIM);
	}
	args[pos] = NULL; // Colocar o último arg como NULL para usar na função execvp
		
	return args;
} 


int main(){

	char line[LINESIZE];
	char **args = (char **) malloc(BUFSIZE * sizeof(char *));
	int c;
	do {
	printf("%%");
	fgets(line, LINESIZE, stdin);
	args = Args(line);
	if(strcmp(args[0], "termina") == 0 && args[1] == NULL) break; // Quando o utilizador escrever termina o programa acaba
	c = MySystem(args[0], args);
	
	printf("Terminou comando %s com codigo %d \n", args[0], c);
	} while(1);
	
	free(args);	

	return 0;
}



		 

		
