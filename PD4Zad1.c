#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

int main(int argc, char **argv)
{
    int a, n, tag = 50;
    float wynik = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &a);
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Status status;

    if(a!=0)
    {
        MPI_Recv(&wynik, 1, MPI_FLOAT, a-1, tag, MPI_COMM_WORLD, &status);
    }

    wynik = wynik + powf(-1, a) / (2 * (a+1) - 1) * 4;

    if(a!=n-1)
    {
        MPI_Send(&wynik, 1, MPI_FLOAT, a+1, tag, MPI_COMM_WORLD);
    }
    else
    {
        printf("Przyblizenie PI = %f\n", wynik);
    }
    MPI_Finalize();
    return 0;
}
