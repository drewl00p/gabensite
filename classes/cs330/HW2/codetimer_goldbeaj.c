/*
	Name: Andrew Goldberg
        Course: CS330
        Date: 9/16/2022
        Homework Label: HW2_Code_Timer
*/

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

void starttimer(struct timeval* s);
void endtimer(struct timeval* e);
void printtimer(struct timeval* s, struct timeval* e);


int main(void)
{
	struct timeval start, end;

	starttimer(&start);	
	sleep(1);
	endtimer(&end);

	printtimer(&start,&end);
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
	long micros = ((seconds * 1000000) + e->tv_usec) - ((seconds * 1000000) + s->tv_usec);
	long microsElapsed = micros % 1000000;

	printf("\nTime elapsed since execution: %ld second(s) and %ld micros.\n\n", seconds, microsElapsed);
}




