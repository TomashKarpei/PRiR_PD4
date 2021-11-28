#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

float funkcja(float x)
{
    return x*x;
}

int main(int argc, char **argv)
{
    int x, n, tag = 50;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &x);
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Status status;

    float wynik = 0, a=1, b=10, dx=(b-a)/n;

    if(x==n-1)
    {
        wynik += funkcja(a + (x*dx)+1);
        MPI_Send(&wynik, 1, MPI_FLOAT, x-1, tag, MPI_COMM_WORLD);
    }

    if((x>=0) && (x < n - 1))
	{
        MPI_Recv(&wynik, 1, MPI_FLOAT, x+1, tag, MPI_COMM_WORLD, &status);
        wynik += funkcja(a + (x+1)*dx);
        if(x!=0)
        {
            MPI_Send(&wynik, 1, MPI_FLOAT, x-1, tag, MPI_COMM_WORLD);
        }
        else
        {
            wynik += (funkcja(a) + funkcja(b))/2;
            printf("Wynik calki = %f\n", dx * wynik);
        }
    }

    MPI_Finalize();
    return 0;
}
