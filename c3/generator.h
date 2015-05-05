#include <time.h>
#include <stdlib.h>

int* generate_random_array(int size) {
	int* random_array = (int*)malloc(sizeof(int)*size);
	int i;
	for(i = 0; i < size; i++) {
		random_array[i] = rand();
	}

	return random_array;
}