#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>

#define M 4
#define N 10000000

//calculates a fragment of pi serie
double calc_serie(int ini) {
	int i;
	int interval = N/M + ini;
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

int main(int argc, char *argv[])
{
	int i, j;
	char* n_threads = NULL; 
	char* serie_length = NULL;
	double* partial_result[M];
	double pi = 0.0;
	char a;
	//getting arguments from command line
	while((a = getopt(argc, argv, "tn:")) != -1) {
		switch(a) {
		case 't': n_threads = optarg; break;
		case 'n': serie_length = optarg; break;
		}
	}

	printf("%s - %s\n", n_threads, serie_length);

	int argument[M];
	//initializing threads
	pthread_t thread[M];
	for (i = 0; i < M; i++)
	{
		argument[i] = i * N/M;
		if(pthread_create(&(thread[i]), NULL, &pi_thread, (void*)&argument[i]) != 0) {
			printf("Can't allocate thread\n");
		}
	}

	//joinning threads - comming back from return
	for (j = 0; j < M; j++)
	{
		 pthread_join(thread[j], (void**)&(partial_result[j]));
		 pi += *partial_result[j];
	}

	printf("%0.12lf\n", 4.0*pi);

	return 0;
}