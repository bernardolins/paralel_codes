#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include "timer.h"

int n_threads; 
int serie_length;

//calculates a fragment of pi serie
double calc_serie(int ini) {
	int i;
	int interval = serie_length/n_threads + ini;
	double result = 0.0;

	for(i = ini; i < interval; i++) {
		result += pow(-1.0, i)*(1.0/(2.0*i + 1.0));
	}

	return result;
}

//thread that calculates pi serie fragment
void* pi_thread(void* init) {
	double* partial_result = (double*)malloc(sizeof(double));
	*partial_result = calc_serie(*(int*)init);
	pthread_exit(partial_result);
}

int main(int argc, char *argv[]) {
	int i, j;
	double** partial_result = (double**)malloc(sizeof(double*)*n_threads);
	double pi = 0.0;
	char a;
	
	//getting arguments from command line
	while((a = getopt(argc, argv, "t:n:")) != -1) {
		switch(a) {
		case 't': n_threads = atoi(optarg); break;
		case 'n': serie_length = atoi(optarg); break;
		}
	}
    double time_ini;
    GET_TIME(time_ini);

	//initializing threads
	int* argument = (int*)malloc(sizeof(int)*n_threads);
	pthread_t* thread = (pthread_t*)malloc(sizeof(pthread_t)*n_threads);

	for (i = 0; i < n_threads; i++) {
		argument[i] = i * serie_length/n_threads;
		if(pthread_create(&(thread[i]), NULL, &pi_thread, (void*)&argument[i]) != 0) {
			printf("Can't allocate thread\n");
		}
	}

	//joining threads - comming back from return
	for (j = 0; j < n_threads; j++) {
		 pthread_join(thread[j], (void**)&(partial_result[j]));
		 pi += *partial_result[j];
	}

    double time_end;
    GET_TIME(time_end);

    double elapsed_time = time_end - time_ini;    
    
    printf("%0.12lf\n", 4.0*pi);
    printf("paralel elapsed time: %0.12lf\n", elapsed_time);
	return 0;
}
