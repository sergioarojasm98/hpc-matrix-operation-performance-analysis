#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
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
    {
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

    if (argc < 2)
    {
        printf("MM1c MatrixSize [Sample arguments ...]\n");
        exit(EXIT_FAILURE);
    }

    N = (int)atof(argv[1]);
    argc--;
    argv++;

    if (N > 1024 * 10)
    {
        printf("Invalid MatrixSize\n");
        exit(EXIT_FAILURE);
    }

    Sample_Init(argc, argv);

#pragma omp parallel private(i, j, k)
    {
        int i, j, k; // Declara las variables aquí
        int NTHR, THR, SZ = N;
        double *a, *b, *c;

        a = MEM_CHUNK;
        b = a + SZ * SZ;
        c = b + SZ * SZ;

// El hilo maestro inicializa las matrices
#pragma omp master
        {
            Matrix_Init_col(SZ, a, b, c);
        }

// Barrera para asegurarse de que la inicialización se ha completado
#pragma omp barrier

        THR = Sample_PAR_install();
        Sample_Start(THR);

// Bucle de multiplicación de matrices
#pragma omp for
        for (i = 0; i < SZ; i++)
        {
            for (j = 0; j < SZ; j++)
            {
                double *pA = a + (i * SZ);
                double *pB = b + j;
                double sum = 0.0;
                for (k = 0; k < SZ; k++, pA++, pB += SZ)
                {
                    sum += (*pA * *pB);
                }
                c[i * SZ + j] = sum;
            }
        }

        Sample_Stop(THR);
    }

    Sample_End();

    return EXIT_SUCCESS;
}
