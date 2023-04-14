#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int matrix1[2][3] = {
    {1, 2, 3},
    {4, 5, 6}};
const int matrix2[3][2] = {
    {0, 1},
    {2, 3},
    {4, 5}};

int calc(int line_num, int line[2]) {
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            line[i] += matrix1[line_num][j] * matrix2[j][i];
}

int main(int argc, char **argv) {
    int id;
    double time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    printf("Process %d starting\n", id);
    time = MPI_Wtime();
    if (id == 0) {
        int res[2][2] = {};
        MPI_Recv(res[0], 2, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(res[1], 2, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("line 0: %d, %d\n", res[0][0], res[0][1]);
        printf("line 1: %d, %d\n", res[1][0], res[1][1]);
    } else if (id <= 2) {
        int line[2] = {};
        calc(id - 1, line);
        MPI_Send(line, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
        // printf("line %d: %d, %d\n", line_num, line[0], line[1]);
    } else {
        printf("Process %d is not used\n", id);
    }
    time = MPI_Wtime() - time;
    printf("Process %d time = %g\n", id, time);

    MPI_Finalize();
    return 0;
}
