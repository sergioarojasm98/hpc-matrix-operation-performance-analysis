#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <mpi.h>
#include "sample.h"

#ifndef MIN
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#endif

#define DATA_SZ (1024 * 1024 * 64 * 3)

static double MEM_CHUNK[DATA_SZ];

void Matrix_Init_col(int SZ, double *a, double *b, double *c)
{
    int j, k;
    for (k = 0; k < SZ; k++)
    { // Se agrega este bucle para iterar sobre 'k'
        for (j = 0; j < SZ; j++)
        {
            a[j + k * SZ] = 2.0 * (j + k);
            b[j + k * SZ] = 3.2 * (j - k);
            c[j + k * SZ] = 1.0;
        }
    }
}

int main(int argc, char **argv)
{
    int N;
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    omp_set_num_threads(MAX_THREADS);

    if (rank == 0)
    {
        printf("MM1f MatrixSize [Sample arguments ...]\n");
    }

    N = (int)atof(argv[1]);
    argc--;
    argv++;

    if (N > 1024 * 10)
    {
        printf("Unvalid MatrixSize\n");
        return -1;
    }

    int startRow = rank * (N / size);
    int endRow = (rank == size - 1) ? N : startRow + (N / size);
    int numRows = endRow - startRow;

    Sample_Init(argc, argv);

    int i, j, k;
    double *a, *b, *c;

    a = MEM_CHUNK;
    b = a + N * N;
    c = b + N * N;

    if (rank == 0)
    {
        // Inicializar matrices en el nodo maestro
        Matrix_Init_col(N, a, b, c);

        // Enviar las matrices a y b a los otros nodos
        for (int p = 1; p < size; p++)
        {
            MPI_Send(a, N * N, MPI_DOUBLE, p, 0, MPI_COMM_WORLD);
            MPI_Send(b, N * N, MPI_DOUBLE, p, 1, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Recv(a, N * N, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(b, N * N, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

#pragma omp parallel private(i, j, k)
    {
        int NTHR, THR, SZ;

        SZ = N;
        THR = Sample_PAR_install();
        NTHR = omp_get_num_threads();

#pragma omp for
        for (i = 0; i < SZ; i++)
            for (j = 0; j < SZ; j++)
            {
                double *pA, *pB, S;
                S = 0.0;
                pA = a + i * SZ;
                pB = b + j * SZ;
                for (k = 0; k < SZ; k++, pA++, pB++)
                    S += *pA * *pB;
                c[i * SZ + j] = S;
            }
    }

    if (rank == 0)
    {
        // Recopilar las partes de c de otros nodos
        for (int p = 1; p < size; p++)
        {
            int start = p * (N / size);
            int end = (p == size - 1) ? N : start + (N / size);
            int num = end - start;
            MPI_Recv(c + start * N, num * N, MPI_DOUBLE, p, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }
    else
    {
        MPI_Send(c + startRow * N, numRows * N, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    Sample_End();
    return 0;
}
