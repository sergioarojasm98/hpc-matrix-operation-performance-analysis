#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <omp.h>

#ifndef MIN
#define MIN(x,y) ((x)<(y)?(x):(y))
#endif

#define DATA_SZ (1024*1024*64*3)

static double MEM_CHUNK[DATA_SZ];

void Matrix_Init_col(int SZ, double *a, double *b, double *c) {
    int j, k;
    for (j = 0; j < SZ; j++) {
        for (k = 0; k < SZ; k++) {
            a[j + k * SZ] = 2.0 * (j + k);
            b[j + k * SZ] = 3.2 * (j - k);
            c[j + k * SZ] = 1.0;
        }
    }
}

int main(int argc, char **argv) {
    int N, rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Process %d out of %d has started.\n", rank, size);

    if (argc < 2) {
        printf("MM1c MatrixSize\n");
        MPI_Finalize();
        return -1;
    }

    N = (int)atof(argv[1]);
    printf("Process %d: Matrix size is %d.\n", rank, N);

    if (N > 1024 * 10) {
        printf("Unvalid MatrixSize\n");
        MPI_Finalize();
        return -1;
    }

    int SZ = N;
    double *a, *b, *c;

    a = MEM_CHUNK;
    b = a + SZ * SZ;
    c = b + SZ * SZ;

    if (rank == 0) {
        printf("Process %d: Before Matrix_Init_col.\n", rank);
        Matrix_Init_col(SZ, a, b, c);
        printf("Process %d: After Matrix_Init_col and before MPI_Bcast.\n", rank);
    }

    MPI_Bcast(a, SZ * SZ, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(b, SZ * SZ, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    printf("Process %d: After MPI_Bcast and before matrix multiplication.\n", rank);

    int rows_per_process = SZ / size;
    int leftover_rows = SZ % size;
    int start_row = rank * rows_per_process;
    int end_row = start_row + rows_per_process;

    if (rank < leftover_rows) {
        start_row += rank;
        end_row += rank + 1;
    } else {
        start_row += leftover_rows;
        end_row += leftover_rows;
    }

    for (int i = start_row; i < end_row; i++) {
       #pragma omp parallel for shared(a, b, c, i, SZ)
        for (int j = 0; j < SZ; j++) {
            double S = 0.0;
            for (int k = 0; k < SZ; k++) {
                S += a[i * SZ + k] * b[k * SZ + j];
            }
            c[i * SZ + j] = S;
        }
    }
    printf("Process %d: After matrix multiplication.\n", rank);

    // Commenting out the suspicious function for debugging purposes
    // Sample_End();

    printf("Process %d: Before MPI_Finalize.\n", rank);
    MPI_Finalize();
    printf("Process %d: After MPI_Finalize.\n", rank);

    return 0;
}
