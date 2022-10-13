
/*
	Name: Andrew Goldberg
        Course: CS330
        Date: 9/16/2022
        Homework Label: HW2_Code_Timer
*/

#define _GNU_SOURCE
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

void forkProcess();
void starttimer(struct timeval* s);
void endtimer(struct timeval* e);
void printtimer(struct timeval* s, struct timeval* e);


int main(void)
{
	struct timeval start, end;
	cpu_set_t mask;
	
	printf("\n");
	printf("-----Multi Processor-----\n");
	starttimer(&start);
	forkProcess();
	endtimer(&end);
	printtimer(&start,&end);

        CPU_ZERO(&mask);
        CPU_SET(0, &mask);
        sched_setaffinity(0, sizeof(cpu_set_t), &mask);

        printf("-----Single Processor-----\n");
        starttimer(&start);
        forkProcess();
        endtimer(&end);
        printtimer(&start,&end);


}

void forkProcess()
{
	volatile int cnt = 0;

	for (int i = 0; i < 5; i++)
	{	
		pid_t pid = fork(); //Fork process			
		
		if(pid == 0) //if child process
		{
			for(int i=0;i<1000000000;i++) {
				cnt++;
			}

			exit(0);
		}
		else if (pid < 0) //if failed fork
		{
			printf("Fork Failed");
			exit(0);
		}
	}
	while(wait(NULL) != -1); //Wait until all child proccesses end
}

//Begins execution timer
void starttimer(struct timeval* s)
{
	gettimeofday(s, NULL);
}

//Ends execution timer
void endtimer(struct timeval* e)
{
	gettimeofday(e, NULL);
}

//Prints execution time
void printtimer(struct timeval* s, struct timeval* e)
{

	long seconds = (e->tv_sec - s->tv_sec);
	long micros = ((seconds * 1000000) + e->tv_usec) -  s->tv_usec;
	long microsElapsed = micros % 1000000;

	printf("\nTime elapsed since execution: %ld second(s) and %ld micros.\n\n", seconds, microsElapsed);
}





