#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void calc_line(int line_A[], int widthA, int *matrixB, int line_C[], int line_C_count) {
    for (int i = 0; i < line_C_count; i++)
        for (int j = 0; j < widthA; j++)
            // line_C[i] += line_A[j] * matrixB[j][i];
            line_C[i] = *(matrixB + i * sizeof(int)) + 2;
}

void calc_chunk(int *partMatrixA, int widthA, int *matrixB, int *partMatrixC, int widthC, int rowsPerProcess) {
    for (int i = 0; i < rowsPerProcess; i++)
        calc_line(partMatrixA + i * widthA * sizeof(int), widthA, matrixB, partMatrixC + i * widthC * sizeof(int), widthC);
}

int main(int argc, char **argv) {
    int rank, size;
    double time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Process %d starting\n", rank);
    time = MPI_Wtime();
    // ----------------------------------------------------

    // Assume matrixA is only available on the root process
    int matrixA[4][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {0, 1, 2}};
    // Assume matrixB is broadcasted to all processes
    int matrixB[3][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8}};

    int heightA = 4;  // sizeof(matrixA) / (sizeof(matrixA[0]) * sizeof(matrixA[0][0]))
    int widthA = 3;   // sizeof(matrixA[0]) / sizeof(matrixA[0][0])
    int heightB = 3;  // sizeof(matrixA) / (sizeof(matrixA[0]) * sizeof(matrixA[0][0]))
    int widthB = 3;   // sizeof(matrixB[0]) / sizeof(matrixB[0][0])

    if (widthA != heightB) {
        printf("the matrices cannot be multiplied\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int heightC = heightA;
    int widthC = widthB;

    // ---------------------------------------------------- scatter

    int rowsPerProcess = heightA / size;
    if (heightA % size) {
        printf("the number of processes must be a divisor of the number of lines\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int partMatrixA[rowsPerProcess][widthA];  // Only relevant for the child processes
    int partMatrixC[rowsPerProcess][widthC];  // Only relevant for the child processes

    MPI_Scatter(matrixA, widthA * rowsPerProcess, MPI_INT, partMatrixA, widthA * rowsPerProcess, MPI_INT, 0, MPI_COMM_WORLD);

    // ---------------------------------------------------- calculate

    // calc_chunk((int *)partMatrixA, widthA, (int *)matrixB, (int *)partMatrixC, widthC, rowsPerProcess);
    for (int row = 0; row < rowsPerProcess; row++)
        for (int i = 0; i < widthC; i++) {
            partMatrixC[row][i] = 0;
            for (int j = 0; j < widthA; j++) {
                partMatrixC[row][i] += partMatrixA[row][j] * matrixB[j][i];
            }
        }
    // ---------------------------------------------------- gather

    // Only necessary on root process
    int matrixC[heightC][widthC];

    MPI_Gather(partMatrixC, widthC * rowsPerProcess, MPI_INT, matrixC, widthC * rowsPerProcess, MPI_INT, 0, MPI_COMM_WORLD);

    // ---------------------------------------------------- print result

    if (rank == 0) {
        printf("\n\n\n");
        for (int i = 0; i < heightC; i++) {
            for (int j = 0; j < widthC; j++)
                printf("%d  ", matrixC[i][j]);
            printf("\n");
        }
    }
    // ----------------------------------------------------
    time = MPI_Wtime() - time;
    printf("Process %d time = %g\n", rank, time);

    MPI_Finalize();
    return 0;
}
