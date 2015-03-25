#include <stdio.h>
#include <stdlib.h>

#define M 4
#define N 10000000

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
	return 0;
}