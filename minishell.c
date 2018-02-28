#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#define MAXLINE 4096

void miniShellInstructions(){
	printf("Welcome to Jenkins' minishell!\n");
	printf("The syntax of the minishell is simple. Just put the command you want to execute followed by the options for execution. You can add up to 4 options to a command, if more than 4 options are entered only the first four will be considered. The syntax for options is '-' followed by the option. For example, in the command 'ls' the option to list all would be written as '-la'. The command should be written first, followed by the options, all seperated by spaces, tabs are not recommended but can be used.\n");	
}

int main(void){
	char   buf[MAXLINE];
	pid_t  pid;
	int    status;
	int    numberOfArguments=0;
	char *tokens[5];
	printf("Type in 'help' for instructions on use.\n");
	printf("> "); /* print prompt)*/
	while (fgets(buf,MAXLINE,stdin) != NULL){
		if(strcmp(buf,"help\n")==0){
		miniShellInstructions();		
		}else{
			
			if(buf[strlen(buf)-1]=='\n')
				buf[strlen(buf) - 1] = '\0';/*replace newline with null */
			for(int i = 0;i<5;i++){
				tokens[i]=(char *)0;
			}
			char *token = strtok(buf, " \t");
			while(token && numberOfArguments<5) {
				tokens[numberOfArguments]=token;
				numberOfArguments++;
				token = strtok(NULL, " \t");
			}
			if((pid = fork())<0 ){
				printf("fork error");
				exit(1);
			}else if(pid==0){/*)child)process)*/
				execlp(tokens[0],tokens[0],tokens[1],tokens[2],tokens[3],tokens[4],(char *)0);
				printf("couldn’t execute: %s \n", buf);
				exit(127);
			}
			/*)parent)process*/
			if((pid=waitpid(pid,&status,0))< 0){
				printf("waitpid error");
				exit(1);
			}
		}
		printf(">");
		numberOfArguments=0;
	}
	exit(0);
}
