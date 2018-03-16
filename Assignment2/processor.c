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

void main()
{
	int shmem_id;
	char *shmem_att;
	char *str; 
	/*the key is given a random integer value. It is kept the same as the one in receiver.c file since we want to get the segment created by the receiver*/
	key_t key = 6200;
	/*The contents read from the shared segment are stored in buff to be written to the file*/
	char *buff = malloc(sizeof(char)*BUFFSIZE);
	FILE * myfile;
	myfile = fopen("digits.out", "w");
	/*Locate the segment created by the receiver. the value of key and flag are the same as in receiver*/
	shmem_id = shmget(key, BUFFSIZE, 0666);
	/*Prints an error if the segment is not located*/
	if(shmem_id < 0)
	{
		printf("Error locating the segment with key %d", key);
	}
	/*The process attaches to the located segment*/
	shmem_att = shmat (shmem_id, NULL , 0);
	/*Prints an error if segment not attached to the process*/
	if(shmem_att < (char*) 0)
	{
		perror("Error in attaching shared memory to data space");
	}
	printf("The located segment is %d\n", shmem_id);

	/*Infinite loop waiting for receiver to send an alphanum string and processing it*/
	while(1)
	{	
		/*check if the contents being read are not NULL*/
		if(*shmem_att!= (int) NULL)
		{
			/*The program appends # after reading every line so that next time it knows that the line would begin with # for as long as new input is not written*/
			if(*shmem_att!='#')
			{
				/*counter keeps track of the digits count*/
				int counter=0;
				int index=0; 
				//initializing str with the line written in the attached segment*/
				str=shmem_att;
				/*receiver has appended * to the end of the line so the processor knows when to stop reading.The loop runs until * is found.*/
				while(*str!='*')				
				{
					/*Contents of str written to buff array*/
					buff[index] = *str;
					/*Checking if the array has a digit and if found incrementing the count*/
					if(isdigit(buff[index]))
					{
						counter++;
					}
					index++;
					str++; 
					
				}
				/*Processor appends # so that it knows it would have to wait for new input the next time*/
				*shmem_att = '#';
				/*New line needs to be appended to the file so opening in append mode*/
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
	}
	
	/*Detatching the attached segment from the process.The segment isn't destroyed as the process would still be able to see the previous contents if they try to attach to the same segment at a later time. The program prints an error on when an erroneous condition occurs. */
	if (shmdt(shmem_att) < 0)
	{
		perror("Error in detaching\n");
	}	
}
