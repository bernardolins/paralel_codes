#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

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
    int pi = 0;
    int serie_length = 0;

    if(MPI_Init(&argc, &argv) == MPI_SUCCESS) {
      MPI_Comm_rank(MPI_COMM_WORD, &rank);
      MPI_Comm_size(MPI_COMM_WORD, &nproc);
    } else {
      printf("-- error while initializing MPI");
    }

    int ini = rank*serie_length/nproc;

    MPI_Finalize();
    return 0;
}
