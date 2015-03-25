#include <stdio.h>
#include <stdlib.h>

#define M 4
#define N 10000000

//thread that calculates pi serie fragment
void* pi_thread(void* init) {
	partial_result = calc_serie(init);

	pthread_exit(&partial_result);
}

//calculates a fragment of pi serie
double calc_serie(int ini) {
	int i;
	int interval = N/M + ini;
	double result = 0.0;

	for(i = ini; i < interval; i++) {
		result += pow(-1.0, i)*(1.0/(2.0*i + 1));
	}

	return result;
}

int main(int argc, char const *argv[])
{
	int i, j;

	double partial_result[M];
	double pi = 0.0;

	//initializing threads
	pthread_t thread[M];
	for (i = 0; i < M; i++)
	{
		if(pthread_create(&(tid[i]), NULL, &pi_thread, NULL) != 0) {
			printf("Can't allocate thread\n");
		}
	}

	//joinning threads - comming back from return
	for (int j = 0; j < M; j++)
	{
		 pthread_join(tid[j], (void**)&(partial_result[j]));
		 pi += partial_result[j];
	}
	
	return 0;
}