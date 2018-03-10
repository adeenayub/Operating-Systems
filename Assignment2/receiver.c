#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

#define BUFFSIZE 1024
int main()
{	
	char *line = malloc(sizeof(char)*BUFFSIZE); 
	char substr[]= "C00L";
	int shmem_id;
	char *shmem_att;
	char *str;
	size_t len; 
	int len1;
	/*the key for the segment is given a random integer value.*/
	key_t key = 6200;
	/*Create a segment*/
	shmem_id = shmget(key, BUFFSIZE, IPC_CREAT | 0666);
	/*Prints an error if the segment is not created*/
	if(shmem_id < 0)
	{
		printf("Error creating a segment with key %d", key);
		return -1;
	}
	/*The process attaches to the created segment*/
	shmem_att = shmat (shmem_id, NULL , 0);
	/*Prints an error if segment not attached to the process*/
	if(shmem_att < (char*) 0)
	{
		perror("Error in attaching shared memory to data space");
		return -1;
	}	

	/*Runs an infinite loop and prompts the user to enter input*/
	while(1)
	{ 
		printf("Enter a string containing alphabets and/or numbers");
		fgets(line, BUFFSIZE, stdin);
		len = strlen(line);

		/*Checks if the string C00L is part of the entered line*/
		if(strstr(line,substr))
		{	
		
			/*Copy the contents of line to shared memory segment*/		//memset(line, 0, sizeof(line));	 
			memcpy(shmem_att, line, len);
			
			str = shmem_att;
			str += len;
			/*Adding a delimiter at the end of the input string so that the processor is able to detect end of line*/
			*str = '*';
			while (*shmem_att != '#')
			{	
				sleep(1);
			}		
		}
		
		
		
	}

	/*Detatching the attached segment from the process.The segment isn't destroyed as the process would still be able to see the previous contents if they try to attach to the same segment at a later time. The program prints an error on when an erroneous condition occurs. */
	if (shmdt(shmem_att) < 0)
	{
		perror("Error in detaching\n");
		return -1;
	}
	/*Removing the shared memory segment*/
	if (shmctl(shmem_id, IPC_RMID, 0) < 0)
	{
		perror("Error in closing\n");
		return -1;
	
	}
	return 0;
}
