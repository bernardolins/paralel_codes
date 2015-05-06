#include "timer.h"
#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int array_size = 0;
int range = 0;

int main(int argc, char *argv[])
{
	char a;
	while((a = getopt(argc, argv, "s:r:")) != -1) {
		switch(a) {
		case 's': array_size = atoi(optarg); break;
		case 'r': range = atoi(optarg); break;
		}
	}

	int* array = generate_random_array(array_size, range);

	return 0;
}