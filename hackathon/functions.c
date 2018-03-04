#include "header.h"

void lot_space(int lot, int sum)
{
	lot = lot - sum;
	printf("Spaces available: %d\n", lot);
}

void text_scan(FILE *infile,int array[], int size)
{
	int index = 0,num=0;
	
	for (; index < size; ++index)
	{
		fscanf(infile, "%d", &num);
		array[index] = num;
		//printf("array[%d]: %d\n", index, num); 
	}
	
}
int sum_array(int array[], int size)
{
	int sum = 0;
	for (int index = 0; index < size; ++index)
	{
		if (array[index] == 1)
		{
			sum++;
		}
	}
	return sum;
}
