#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

double pi_serial(int n) {
  double result = 0.0;
  int i = 0;
  for (i = 0; i < n; i++)
  {
    result += pow(-1.0, i)*(1.0/(2.0*i + 1));
  }

  return 4.0*result;
}

int main(int argc, char* argv[]) {
    if(MPI_Init(&argc, &argv) == MPI_SUCCESS) {

    } else {
      printf("-- error while initializing MPI");
    }

    MPI_Finalize();
    return 0;
}
