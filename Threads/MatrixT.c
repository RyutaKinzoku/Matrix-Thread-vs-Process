#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>

int global[825];
int result[825][825];
FILE* res;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct arguments
{
    int row[825];
    int cols[825][825];
    int p;
    unsigned long i;
    int res[825];
};
int result[825][825];
struct arguments args;

void *multiply(void *arg)
{
    struct arguments *actual_args = arg;
    int p = actual_args->p;
    int actual_row = 0;
    for (int j = 0; j < actual_args->p; j++)
    {
        for (int i = 0; i < actual_args->p; i++){
            
            actual_args->res[j] += actual_args->row[i]*actual_args->cols[j][i];
        }
    }
    int q=p-1;
    while (q >= 0)
    {
        result[actual_args->i][q] = actual_args->res[q];
        actual_args->res[q] = 0;
        q--;
    }
    pthread_exit(NULL);
}

int main()
{

    unsigned short j, n, k;

    /*time_t rawtime1;
    time_t rawtime2;*/
    struct timespec spec;

    printf("Matrix Thread: \n");
    //printf("Enter the dimension of the matrix: ");
    //scanf("%hu", &n);
    n=10;
    int matrix1[n][n];
    int matrix2[n][n];
    unsigned int randval;
    FILE *f;
    for(int i = 0; i < n;i++) {
    	for(j = 0; j < n;j++) {
            f = fopen("/dev/random", "r");
            fread(&randval, sizeof(randval), 1, f);
            fclose(f);
            matrix1[i][j] = randval%10;
            f = fopen("/dev/random", "r");
            fread(&randval, sizeof(randval), 1, f);
            fclose(f);
            matrix2[i][j] = randval%10;
            result[i][j] = 0;
    	}
    }
    res = fopen("Mat_R.txt", "w");
    clock_t begin = clock();
    pthread_t threads[n];
    args.p = n;
    for (int q = 0; q < n; q++)
    {
        for (int s = 0; s < n; s++)
        {
            args.cols[q][s] = matrix2[s][q];
        }
    }
    for (long i = 0; i < n; i++)
    {
        for (int p = 0; p < n; p++)
        {
            args.row[p] = matrix1[i][p];
        }
        args.i = i;
        pthread_create(&threads[args.i], NULL, &multiply, &args);
        sleep(0);
    }
    int q=n-1;
    while (q >= 0)
    {
        pthread_join(threads[q], NULL);
        q--;
    }

    clock_t end = clock();
    double time = (double)(end - begin) / CLOCKS_PER_SEC;
    FILE* stats = fopen("Stats.txt", "a+");
    fprintf(stats, "%f\n", time);
    printf("%f nanoseconds\n", time);
    for(int i = 0; i < n;i++) {
        for(j = 0; j < n;j++) {
            fprintf(res, "%d\t", result[i][j]);
        }
        fprintf(res, "\n");
    }
    return 0;
}