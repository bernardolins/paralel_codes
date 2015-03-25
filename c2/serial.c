#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double pi_serial(int n) {
	double result = 0.0;
	int i = 0;
	for (i = 0; i < n; i++)
	{
		result += pow(-1.0, i)*(1.0/(2.0*i + 1));
	}

	return 4.0*result;
}


int main(int argc, char const *argv[])
{
	printf("%0.10lf\n", pi_serial(10000000));
	return 0;
}