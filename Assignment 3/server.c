//This is incomplete
#include <stdio.h>
#include <sys/socket.h>
#define PORT 80
#define BUFFSIZE 1024

int sockid, status, serv_accept, data_count, new_sock;
struct sockaddr_in serv_address, client_address;
socklen_t* clientaddr_len;
char *buff = malloc(sizeof(char)*BUFFSIZE);
 
int main()
{
	printf("Assalamualaikum! I am the server. Nice to see you!\n");
	sockid = socket(AF_INET,SOCK_STREAM ,0);
	if(sockid == 0)
	{
		perror("Failed to create a socket");
z		exit(1);
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
		perrror("The server has failed to listen on this port ");
		exit(1);
	}
	printf("The server is listening\n");
	clientaddr_len = sizeof(client_addr);
	new_sock = accept(sockid, (struct sockaddr *)&client_addr, &clientaddr_len);
	if(new_sock < 0)
	{
		perror("Error in accepting. Connection not established.");
		exit(1);
	}
	if(recv(new_sock, buff, BUFFSIZE, 0) < 0)
	{
		perror("Error in receiving the message from the client");
		exit(1);
	}
	
	
	return 0;
}
