#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#define MAXLINE 4096


/*
	Small function that prints a text containing instructions on how to use the shell.
*/
void miniShellInstructions(){
	printf("Welcome to Jenkins' minishell!\n");
	printf("The syntax of the minishell is simple. Just put the command you want to execute followed by the options for execution. You can add up to 4 options to a command, if more than 4 options are entered only the first four will be considered. The syntax for options is '-' followed by the option. For example, in the command 'ls' the option to list all would be written as '-la'. The command should be written first, followed by the options, all seperated by spaces, tabs are not recommended but can be used.\n");	
}

int main(void){
	char   buf[MAXLINE]; 		// Array that contains string to be read
	pid_t  pid;					// Structure that holds the child created by fork
	int    status;				// Used for parent that will read child exit status
	int    numberOfArguments=0;	// Used to know how many arguments are being read
	char *tokens[5];			// Array of pointers to strings
	printf("Type in 'help' for instructions on use.\n"); //Display instructions on how to use the help command
	printf("> "); /* print prompt)*/
	while (fgets(buf,MAXLINE,stdin) != NULL){ //We read the standard input and save text into our buf array
		if(strcmp(buf,"help\n")==0){ //If help is needed display instructions
		miniShellInstructions();		
		}else{
			if(buf[strlen(buf)-1]=='\n')
				buf[strlen(buf) - 1] = '\0';/*replace newline with null */
			for(int i = 0;i<5;i++){
				tokens[i]=(char *)0; //Make our array empty
			}
			char *token = strtok(buf, " \t"); // Tokenize our text entered to get the command and options
			while(token && numberOfArguments<5) { 
				tokens[numberOfArguments]=token; 
				numberOfArguments++;
				token = strtok(NULL, " \t");
			}
			if((pid = fork())<0 ){ // Check if our fork produced error
				printf("Fork error");
				exit(1);
			}else if(pid==0){/*)child)process)*/
				execlp(tokens[0],tokens[0],tokens[1],tokens[2],tokens[3],tokens[4],(char *)0); // We pass all of our array values as parameters, as some are empty it does not effect execution
				printf("Couldn’t execute: %s \n", buf); //In case of error display message and return 127 exit status
				exit(127);
			}
			/*)parent)process*/
			if((pid=waitpid(pid,&status,0))< 0){ // In case we have a problem with our fork it is caught be a parent
				printf("Waitpid error"); 
				exit(1);
			}
		}
		printf(">"); // Print prompt
		numberOfArguments=0; // Reset our counter for number of arguments
	}
	exit(0); //Exit succesfully
}
