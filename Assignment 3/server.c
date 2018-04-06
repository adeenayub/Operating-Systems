//Works perfectly fine Alhamdullilah
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <ctype.h> /*for isdigit*/
#define PORT 8080
#define BUFFSIZE 1024

int sockid, status, serv_accept, data_count, new_sock;
struct sockaddr_in serv_address, client_address;
socklen_t clientaddr_len;
char *buff;
char *str, *line;
int counter;
 
void CountDigits()
{
	line[BUFFSIZE] = '\0';
	counter = 0;
	int index = 0;
	str = line;
	
	while(*line!='\0')
	{	/*Contents of str written to buff array*/
		buff[index] = *line;
		/*Checking if the array has a digit and if found incrementing the count*/
		if(isdigit(buff[index]))
		{
			counter++;
		}
		index++;
		line++; 
			
	}
	
}
static void Readfile(const char * fname)
{
    FILE *f = fopen(fname, "r");    
    if(f != NULL)
    {
        int ch;

        while((ch = fgetc(f)) != EOF)     
        {
            putchar(ch);      
        }
        fclose(f);
    }
}

void DisplaySum(int a)
{
	
	Readfile("digits.out");
}

int main()
{
	line = malloc(sizeof(char)*BUFFSIZE);
	buff = malloc(sizeof(char)*BUFFSIZE);
	FILE * myfile;
	int opt = 1;
	struct sigaction sgact;
    	sgact.sa_handler = DisplaySum;
	myfile = fopen("digits.out", "w");
	printf("Assalamualaikum! I am the server. Nice to see you!\n");
	sockid = socket(AF_INET,SOCK_STREAM ,0);
	if(sockid == 0)
	{
		perror("Failed to create a socket");
		exit(1);
	}
	if (setsockopt(sockid, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
   	{
       		perror("setsockopt");
        	exit(EXIT_FAILURE);
    	}
	serv_address.sin_family = AF_INET;
    	serv_address.sin_addr.s_addr = INADDR_ANY;
    	serv_address.sin_port = htons( PORT );
	if (bind(sockid, (struct sockaddr *)&serv_address,
					sizeof(serv_address))<0)
	{
		perror("Failed to bind the socket");
		exit(1);
	}
	if(listen(sockid, 1) < 0)
	{
		perror("The server has failed to listen on this port ");
		exit(1);
	}
	printf("The server is listening\n");
	//sigaction(SIGINT, &sgact, NULL);
	
	clientaddr_len = sizeof(client_address);
	
	
	new_sock = accept(sockid, (struct sockaddr *)&client_address, 							&clientaddr_len);
	if(new_sock < 0)
	{
		perror("Error in accepting. Connection not established.");
		exit(1);
	}
	
	sigaction(SIGINT, &sgact, NULL);
	
	while(1)
	{
		if(recv(new_sock, line, BUFFSIZE, 0) < 0)
		{
			;
		}
		
		else
		{
			CountDigits();
			myfile= fopen("digits.out","a");
					
			if(myfile!=NULL)
			{
				/*Printing the count of digits*/
				fprintf(myfile,"Count is %d for line: ", counter);	
				/*Printing the line containing the word C00L*/
				fprintf(myfile, "%s",buff);
				fclose(myfile);
			}
				/*Emptying the contents of buffer everytime*/
				memset(buff, 0, BUFFSIZE);
		}
	}
	return 0;	
}

