#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int* generate_random_array(int size, int range) {
	int* random_array = (int*)malloc(sizeof(int)*size);
	int i;
	for(i = 0; i < size; i++) {
		random_array[i] = (rand() % range);
	}

	return random_array;
}