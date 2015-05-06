#include "timer.h"
#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>

int array_size = 0;
int range = 0;
int n_threads = 0;
int* array; 

int* results;

void* tprefix_sum(void* arg) {
	int start_count = *(int*)arg;
	int i;
	int last = start_count + array_size/n_threads;
	for(i = start_count + 1; i < last; i++) {
		array[i] += array[i-1];
	}

	results[start_count/(array_size/n_threads)] = array[last];
	return NULL;
}

int main(int argc, char *argv[])
{
	char a;
	while((a = getopt(argc, argv, "s:r:t:")) != -1) {
		switch(a) {
		case 's': array_size = atoi(optarg); break;
		case 'r': range = atoi(optarg); break;
		case 't': n_threads = atoi(optarg); break;
		}
	}

	array = generate_random_array(array_size, range);

	double time_ini;
    GET_TIME(time_ini);

	results = (int*)malloc(sizeof(int)*n_threads);


	pthread_t* thread = (pthread_t*)malloc(sizeof(pthread_t)*n_threads);
	int* start_count = (int*)malloc(sizeof(int)*n_threads);

//	print_generated(array, array_size);

	int i;
	for (i = 0; i < n_threads; i++) {
		start_count[i] = i * array_size/n_threads;
		if(pthread_create(&(thread[i]), NULL, &tprefix_sum, (void*)&start_count[i]) != 0) {
			printf("Can't allocate thread\n");
		}
	}

//	printf("\n");
//	print_generated(array, array_size);
	
	int j;
	for(j = 0; j < n_threads; j++) {
		pthread_join(thread[j], NULL);
	}

	double time_end;
    GET_TIME(time_end);

    printf("paralel time: %0.12lf\n", (time_end - time_ini));

	return 0;
}