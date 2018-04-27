#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <rpc/rpc.h>
#include "dgc.h"

#define BUFFSIZE 1024

int main(int argc, char **argv)
{
	CLIENT *c1;
	char *server;
	FILE * myfile;
	myfile = fopen("digits.out", "w");
	if(argc!=2)
	{
		printf("Too less arguments\n");
		exit(1);
	}

	server = argv[1];
	while(1)
	{
		if ((c1=clnt_create(server, DIGITSCOMPUTE_PROG, DIGITSCOMPUTE_VERS , "udp")) == NULL)
		{
			clnt_pcreateerror(server);
			exit(1);
		}

	
		char *myline = malloc(sizeof(char)*BUFFSIZE); 
		char substr[]= "C00L";
		printf("Enter a string containing alphabets and/or numbers  ");
		fgets(myline, BUFFSIZE, stdin);
		int len = strlen(myline);
		if((strstr(myline, substr)))
		{		
			printsum_1(&myline, c1);
		}
	}	
	clnt_destroy(c1);
	return 0;
}
