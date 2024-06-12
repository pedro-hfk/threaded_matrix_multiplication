#include "threaded.h"
#include <stdio.h>

void *multiply_parallel(void *arg)
{
    thread_data_t *data = (thread_data_t *)arg;
    int start_row = data->start_row;
    int end_row = data->end_row;
    int matrix_size = data->matrix_size;
    int **A = data->A;
    int **B = data->B;
    int **C = data->C;
    sem_t *sem = data->sem;

    for (int i = start_row; i < end_row; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            int sum = 0;
            for (int k = 0; k < matrix_size; k++)
            {
                sum += A[i][k] * B[k][j];
            }
            sem_wait(sem); // Espera pelo semáforo
            C[i][j] = sum;
            sem_post(sem); // Libera o semáforo
        }
    }

    pthread_exit(NULL);
}
