/* 
	Program 0 for CS220
	Written by Andrew Goldberg
	Jan 2022
	Language: C
*/


#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Provide a single filename.\n");
		exit(EXIT_FAILURE);
	}

	FILE *read_ptr = fopen(argv[1], "r");
	if (read_ptr == NULL)
	{
		perror("The file didn't open correctly");
		exit(EXIT_FAILURE);
	}	

	unsigned int line_no = 1;
	unsigned int count = 0;
	int num = 0;
	int min = 0;
	int sum = 0;
	int freq[21] = {0};
	int median = 0;
	char c;
	

	//Repeats until < 2 inputs are returned from fscanf
	while (fscanf(read_ptr, "%d%c", &num, &c) == 2) {

		if (count == 0) {
			min = num;
			median = num;
		}

		//Check for smallest # in line
		if (num < min)
			min = num;

		//Add num to sum of all #'s in line
		sum += num;

		//Increments frequency of the current number (-10 to 10)
		freq[num + 10] += 1;

		count++;

		if (c =='\n') {

			//Determine median
			for (int i = 0; i < 21; i++)
			{
				if (freq[i] > freq[median + 10])
					median = i - 10;
				else if (freq[i] == freq[median + 10] && i - 10 > median - 10)
					median = i - 10;
			}

			printf("%d %d %d %d\n", line_no, sum, min, median);

			//Set all item freqency array elements to 0
			for (int i = 0; i < 21; i++)
			{
				freq[i] = 0;
			}

			count = 0;
			sum = 0;
			line_no++;
		}
	}

	fclose(read_ptr);
	exit(EXIT_SUCCESS);
}