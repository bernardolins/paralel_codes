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

typedef struct args
{
	int start_count;
	int sum_value;
} targs;

void* tprefix_sum(void* arg) {
	int start_count = *(int*)arg;
	int i;
	int last = start_count + (array_size/n_threads) -1;
	for(i = start_count; i < last; i++) {
		array[i+1] += array[i];
	}

	results[start_count/(array_size/n_threads)] = array[last];
	return NULL;
}

void* adjust_values(void* args) {
	targs* arguments = args;
	int start = arguments->start_count;
	int value = arguments->sum_value;
	int last = start + (array_size/n_threads) - 1;
	int i;

	for(i = start; i <= last; i++) {
		array[i] += value;
	}

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
	targs* args = (targs*)malloc(sizeof(targs)*n_threads);
	
	int* start_count = (int*)malloc(sizeof(int)*n_threads);

	// print_generated(array, array_size);
	// printf("\n");

	int i;
	for (i = 0; i < n_threads; i++) {
		start_count[i] = i * array_size/n_threads;
		
		if(pthread_create(&(thread[i]), NULL, &tprefix_sum, (void*)&start_count[i]) != 0) {
			printf("Can't allocate thread\n");
		}
	}

	int j;
	for(j = 0; j < n_threads; j++) {
		pthread_join(thread[j], NULL);
	}


	int k, acumulated = 0;
	for(k = 0; k < n_threads-1; k++) {
		acumulated += results[k];
		args[k].sum_value = acumulated;
		args[k].start_count = start_count[k+1];
		
		if(pthread_create(&	(thread[k]), NULL, &adjust_values, &args[k])) {
			printf("Can't allocate thread\n");
		}
	}

	for(j = 0; j < n_threads-1; j++) {
		pthread_join(thread[j], NULL);
	}

	// print_generated(array, array_size);
	// printf("\n");

	double time_end;
  GET_TIME(time_end);

  printf("paralel time: %0.12lf\n", (time_end - time_ini));

	return 0;
}