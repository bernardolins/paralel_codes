#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <ctype.h>
#include "mpi.h"
#include "timer.h"

double pi_serial(int ini, int end) {
  double result = 0.0;
  int i = ini;
  for (i = ini; i < end; i++)
  {
    result += pow(-1.0, i)*(1.0/(2.0*i + 1));
  }

  return result;
}

int main(int argc, char* argv[]) {
    int rank, nproc;
    double pi = 0, local_sum = 0;
    long int serie_length = 0;

    char a;
    while((a = getopt(argc, argv, "n:")) != -1) {
      switch(a) {
      case 'n': serie_length = atoi(optarg); break;
      }
    }

    double time_ini;
    GET_TIME(time_ini);

    if(MPI_Init(&argc, &argv) == MPI_SUCCESS) {
      MPI_Comm_rank(MPI_COMM_WORLD, &rank);
      MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    } else {
      printf("-- error while initializing MPI");
    }

    int ini = rank*serie_length/nproc;
    int end = ini + serie_length;

    local_sum = pi_serial(ini, end);

    MPI_Reduce(&local_sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    MPI_Finalize();

    double time_end;
    GET_TIME(time_end);

    if(rank == 0) {
      pi *= 4.0;
      printf("result: %0.12lf\n", pi);
      printf("time: %0.12lf\n", time_end-time_ini);
    }

    return 0;
}
