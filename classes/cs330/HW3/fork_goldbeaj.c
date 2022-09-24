/*
 * Name: Andrew Goldberg
 * Course: CS330
 * Date: 9.23.22
 * Label: HW3_Basic_Forking
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{
	for (int i = 0; i < 12; i++)
	{

		char letter = 'A';

		for (int i = 0; i < 26; i++)
		{	

			pid_t pid = fork(); //Fork process
			
			if(pid == 0) //if child process
			{
				printf("%c",letter);
				exit(0);
			}
			else if (pid < 0) //if failed fork
			{
				printf("Fork Failed");
				exit(0);
			}
			letter++;
		}
		while(wait(NULL) != -1); //Wait until all child proccesses end
		
		printf("\n");
	}
	return 0;
}






