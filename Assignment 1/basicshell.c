#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void PromptUser()
{
	printf("\n\n\n***************************************************\n");
	printf("***************************************************\n");
	printf("**************BASIC SHELL PROGRAM******************\n");
	printf("***************************************************\n");
	printf("***************************************************\n");
	printf("*******Assalamualaikum(May peace be on you)!*******\n");
	printf("***************************************************\n");
	printf("***************************************************\n");
	printf("***************************************************\n");
	
	printf("Please enter a command\n");
}

char* ReadCommand()
{
	char *line = NULL;
	size_t buffsize= 100;
	/*get user input as a single line*/
	getline(&line, &buffsize, stdin); 
	return line;
	
}

char** ParseCommand(char *line, char **tokenarray)
{  
	char *token;
	int status;
	int size = 100; 
	int index = 0;
	/*dynamically allocating memory to the tokenarray based on the arguments*/
	tokenarray = (char**) malloc(sizeof(char*));
/*line gets tokenized based on the delimiters*/
	token = strtok(line, " \t\r\n\a\f\v");
	while(token!=NULL) /*going through all tokens and giving each a place in tokenarray*/
		{
			tokenarray[index] = token;
			index = index+1; 
			/*if the size of tokenarray becomes greater than the memory allocated to it, reallocate it some more memory*/
			if(index>size)
			{
				tokenarray = realloc(tokenarray, sizeof(char*));
				size +=size;
			}		
			token = strtok(NULL, "\0"); 
		} /*null termination of the list of tokens*/ 
	tokenarray[index] = NULL;
	return tokenarray;
}

void executecmd()
{
	
		int status;
		char *line;
		char *argv[100];
		char **parsed;
		PromptUser();/*the function prompts the user to enter a command*/
		line= ReadCommand();/*the entered command gets read as a line*/
		parsed = ParseCommand(line, argv); /*the command gets parsed into arguments so that can be executed*/
		pid_t pid = fork();  /*creating or forking a child process*/
		if(pid==0)
		{
			printf("This is the child process with pid %d\n", getpid());
			/*child executes the command and exits if an error occurs*/
			if(execvp(*parsed,parsed)== -1) 
			{
				exit(EXIT_FAILURE);
			}
			
		}
		else if(pid<0) /*if an error occurs in forking the process*/
		{
			perror("Couldn't create a child");
		}
		else /*the parent process gets called first after which it copies all the information to the child process*/
		{
			printf("This is the parent process with pid %d\n", getpid());       
			while (wait(&status) != pid) /*Parent waiting for child to get done*/
				;        
		 }

}

void main()
{
	while(1)
	{	
		executecmd();
	}
}
