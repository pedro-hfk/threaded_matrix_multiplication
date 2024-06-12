#ifndef THREADED_H
#define THREADED_H

#include <pthread.h>
#include <semaphore.h>

typedef struct
{
    int start_row;
    int end_row;
    int matrix_size;
    int **A;
    int **B;
    int **C;
    sem_t *sem;
} thread_data_t;

void *multiply_parallel(void *arg);

#endif
