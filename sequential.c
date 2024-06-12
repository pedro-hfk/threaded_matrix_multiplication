#include "sequential.h"

int **multiply_sequential(int **A, int **B, int matrix_size)
{
    int **C = malloc(matrix_size * sizeof(int *));
    for (int i = 0; i < matrix_size; i++)
    {
        C[i] = malloc(matrix_size * sizeof(int));
    }

    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < matrix_size; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}
