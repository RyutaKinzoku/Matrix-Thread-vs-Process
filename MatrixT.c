#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>

int global = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct arguments
{
    int row[825];
    int cols[825][825];
    int p;
    unsigned long i;
    int res[825];
};

struct arguments args;

void *multiply(void *arg)
{
    struct arguments *actual_args;
    actual_args = (struct arguments *)arg;
    int p = actual_args->p;
    for(int i=0;i<p;i++){
            row[i] =  actual_args->row[i];
        }
    for (int j = 0; j < actual_args->p; j++)
    {
        for (int i = 0; i < actual_args->p; i++){
            actual_args->res[j] += row[actual_row]*actual_args->cols[j][actual_row];
            pthread_mutex_lock(&mutex);
            /*printf("%d ", row[actual_row]);*/
            printf("%d ", actual_args->res[j]);
            /*printf("%d\n", cols[j][i]);*/
            pthread_mutex_unlock(&mutex);
        }
        actual_row++;
    }
    /*unsigned long i = (long)actual_args->i;
    printf("Thread %ld\n", i);*/
    pthread_exit(NULL);
}

int main()
{

    unsigned short j, n, k;

    time_t rawtime1;
    time_t rawtime2;
    struct timespec spec;

    printf("Matrix Thread: \n");
    printf("Enter the dimension of the matrix: ");
    scanf("%hu", &n);
    int matrix1[n][n];
    int matrix2[n][n];
    int result[n][n];

    for (int i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            /*srand(time(0));*/
            matrix1[i][j] = rand() % 10;
            matrix2[i][j] = rand() % 10;
            result[i][j] = 0;
        }
    }

    clock_gettime(CLOCK_REALTIME, &spec);
    rawtime1 = spec.tv_sec;
    pthread_t threads[n];
    args.p = n;
    for (long i = 0; i < n; i++)
    {
        for (int q = 0; q < n; q++)
        {
            for (int s = 0; s < n; s++)
            {
                args.cols[q][s] = matrix2[s][q];
            }
        }
        for (int p = 0; p < n; p++)
        {
            args.row[p] = matrix1[i][p];
            /*printf("%d",args.row[p]);*/
        }
        printf("\n");
        args.i = i;
        pthread_create(&threads[i], NULL, multiply, &args);
        result[i][i] = global;
    }
    for (int q = 0; q < n; q++)
    {
        pthread_join(threads[q], NULL);
    }
    
    clock_gettime(CLOCK_REALTIME, &spec);
    rawtime2  = spec.tv_sec;
    printf("\n");
    for(int i = 0; i < n;i++) {
        for(j = 0; j < n;j++) {
            printf("%d ", matrix1[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(int i = 0; i < n;i++) {
        for(j = 0; j < n;j++) {
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(int i = 0; i < n;i++) {
        for(j = 0; j < n;j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    return 0;
}