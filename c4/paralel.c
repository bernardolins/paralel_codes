#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <ctype.h>
#include <omp.h>
#include "timer.h"

int* tasks;
int current_task = 0;
double result = 0.0;

double pi_serial(int n) {
	int current = 0;
	result = 0.0;

	#pragma omp critical
	current = current_task;
	current_task++;

	int i;
	for (i = tasks[current]; i < n + tasks[current]; i++)
	{
		result += pow(-1.0, i)*(1.0/(2.0*i + 1));
	}

	return result;
}

int main(int argc, char *argv[]) {
	char a;
    int serie_length, n_threads;
    //getting arguments from command line
    while((a = getopt(argc, argv, "n:t:")) != -1) {
        switch(a) {
        case 'n': serie_length = atoi(optarg); break;
        case 't': n_threads = atoi(optarg); break;
        }
    }

    tasks = (int*)malloc(sizeof(int)*n_threads);

    int i;
    for(i = 0; i < n_threads; i++) {
    	tasks[i] = i*serie_length/n_threads;
    }

	double time_ini;
    GET_TIME(time_ini);

	#pragma omp parallel
	result += pi_serial(serie_length/n_threads);

	double time_end;
    GET_TIME(time_end);

    printf("-- serial time: %0.12lf\n", time_end - time_ini);

    printf("%0.12lf\n", 4.0*result);

	return 0;
}