#include "timer.h"
#include <stdio.h>
#include <stdlib.h>

int int main(int argc, char const *argv[])
{
	char a;
	while((a = getopt(argc, argv, "s:")) != -1) {
		switch(a) {
		case 's': n_threads = atoi(optarg); break;
		}
	}

	return 0;
}