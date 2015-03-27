#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include "timer.h"

double pi_serial(int n) {
	double result = 0.0;
	int i = 0;
	for (i = 0; i < n; i++)
	{
		result += pow(-1.0, i)*(1.0/(2.0*i + 1));
	}

	return 4.0*result;
}


int main(int argc, char *argv[])
{
    char a;
    int serie_length;
    //getting arguments from command line
    while((a = getopt(argc, argv, "n:")) != -1) {
        switch(a) {
        case 'n': serie_length = atoi(optarg); break;
        }
    }
    
     double time_ini;
     GET_TIME(time_ini);


    double pi = pi_serial(serie_length);
    
    double time_end;
    GET_TIME(time_end);
    

    double elapsed_time = time_end - time_ini;
	printf("%0.12lf\n", pi);


    printf("serial elapsed time: %0.12lf\n", elapsed_time);
	return 0;
}
