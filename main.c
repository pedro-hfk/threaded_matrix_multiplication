#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include "threaded.h"
#include "sequential.h"

#ifndef MATRIX_SIZE
#define MATRIX_SIZE 10
#endif

#ifndef NUM_THREADS
#define NUM_THREADS 4
#endif

void initialize_matrix(int **matrix, int size, int add, int subtract)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = add ? (i + j) : (i - j);
        }
    }
}

void free_matrix(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int main()
{
    int matrix_size = MATRIX_SIZE;
    int num_threads = NUM_THREADS;

    printf("Number of threads: %d\n", num_threads);

    int **A = malloc(matrix_size * sizeof(int *));
    int **B = malloc(matrix_size * sizeof(int *));
    int **C = malloc(matrix_size * sizeof(int *));
    int **D = malloc(matrix_size * sizeof(int *));
    for (int i = 0; i < matrix_size; i++)
    {
        A[i] = malloc(matrix_size * sizeof(int));
        B[i] = malloc(matrix_size * sizeof(int));
        C[i] = malloc(matrix_size * sizeof(int));
        D[i] = malloc(matrix_size * sizeof(int));
    }

    // Inicialização das matrizes A e B com valores
    initialize_matrix(A, matrix_size, 1, 0);
    initialize_matrix(B, matrix_size, 0, 1);

    pthread_t threads[num_threads];
    thread_data_t thread_data[num_threads];
    sem_t sem;

    sem_init(&sem, 0, 1); // Inicializa o semáforo

    clock_t parallel_start = clock();

    int block_size = matrix_size / num_threads;
    for (int i = 0; i < num_threads; i++)
    {
        thread_data[i].start_row = i * block_size;
        thread_data[i].end_row = (i == num_threads - 1) ? matrix_size : (i + 1) * block_size;
        thread_data[i].matrix_size = matrix_size;
        thread_data[i].A = A;
        thread_data[i].B = B;
        thread_data[i].C = C;
        thread_data[i].sem = &sem;

        pthread_create(&threads[i], NULL, multiply_parallel, &thread_data[i]);
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    clock_t parallel_end = clock();

    clock_t sequential_start = clock();

    D = multiply_sequential(A, B, matrix_size);

    clock_t sequential_end = clock();

    double parallel_time = (double)(parallel_end - parallel_start) / CLOCKS_PER_SEC;
    double sequential_time = (double)(sequential_end - sequential_start) / CLOCKS_PER_SEC;

    printf("\nMatrix size: %d\n", matrix_size);
    printf("Parallel time: %f\n", parallel_time);
    printf("Sequential time: %f\n", sequential_time);
    printf("Speedup Rate: %f\n", sequential_time / parallel_time);

    // Liberação da memória alocada
    free_matrix(A, matrix_size);
    free_matrix(B, matrix_size);
    free_matrix(C, matrix_size);
    free_matrix(D, matrix_size);

    sem_destroy(&sem); // Destroi o semáforo

    return 0;
}
