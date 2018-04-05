#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFSIZE 1024

int skt = 0;
struct sockaddr_in serv_address; 

void main()
{
	char *line = malloc(sizeof(char)*BUFFSIZE); 
	char *buff = malloc(sizeof(char)*BUFFSIZE);
	char substr[]= "C00L";
	char *str;
	int len;
	printf("Assalamualaikum! I am the client. Nice to see you!");
	skt = socket(AF_INET,SOCK_STREAM ,0);
	if(skt < 0)
	{
		perror("Socket not created\n");
		exit(1);
	}
	memset(&serv_address, '0', sizeof(serv_address));
	serv_address.sin_family = AF_INET;
    	serv_address.sin_port = htons( PORT );

	if(inet_pton(AF_INET, "127.0.0.1", &serv_address.sin_addr)<=0) 
    	{
		perror("The address is not valid \n");
		exit(1);
    	}
	if (connect(skt, (struct sockaddr *)&serv_address, sizeof(serv_address)) < 0)
    	{
        	printf("The client has failed to connect to server \n");
        	exit(1);
    	}
	//while(1)
	//{
		printf("Enter a string containing alphabets and/or numbers");
		fgets(line, BUFFSIZE, stdin);
		printf("%s", line);
		len = strlen(line);
		if(strstr(line,substr))
		{
			send(skt,line,strlen(line),0 );
		}	
	//}
	
}
