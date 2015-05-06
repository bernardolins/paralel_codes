#include "timer.h"
#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	char a;
	int array_size = 0, range = 0;

	while((a = getopt(argc, argv, "s:r:")) != -1) {
		switch(a) {
		case 's': array_size = atoi(optarg); break;
		case 'r': range = atoi(optarg); break;
		}
	}

	int* array = generate_random_array(array_size, range);
	
	double time_ini;
    GET_TIME(time_ini);

	int i;
	for(i = 1; i < array_size; i++) {
		array[i] += array[i-1];
	}
	
	double time_end;
    GET_TIME(time_end);

    printf("-- serial time: %0.12lf\n", time_end - time_ini);

	return 0;
}