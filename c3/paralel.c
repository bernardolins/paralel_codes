#include "timer.h"
#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int array_size = 0;
int range = 0;
int n_threads = 0; 

int* results;

void* tprefix_sum(void* arg) {
	//pega 1/t do array
	//soma normalmente
	//pega o ultimo elemento e coloca no array results
}

int main(int argc, char *argv[])
{
	char a;
	while((a = getopt(argc, argv, "s:r:")) != -1) {
		switch(a) {
		case 's': array_size = atoi(optarg); break;
		case 'r': range = atoi(optarg); break;
		case 't': n_threads = atoi(optarg); break;
		}
	}

	results = (int*)malloc(sizeof(int)*n_threads);

	int* array = generate_random_array(array_size, range);

	pthread_t* thread = (pthread_t*)malloc(sizeof(pthread_t)*n_threads);
	int* start_count = (int*)malloc(sizeof(int)*n_threads);

	for (i = 0; i < n_threads; i++) {
		start_count[i] = i * array_size/n_threads;
		if(pthread_create(&(thread[i]), NULL, &tprefix_sum, (void*)&start_count[i]) != 0) {
			printf("Can't allocate thread\n");
		}
	}

	return 0;
}