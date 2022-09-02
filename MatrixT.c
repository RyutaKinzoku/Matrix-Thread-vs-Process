#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h> 
#include <unistd.h>

int global = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
typedef struct arguments
{
    int row[825];
    int col[825];
    int p;
    int res;
} args;

void* multiply(void *arg){
    struct arguments *actual_args = arg;
    actual_args->res = 0;
    for (int j = 0; j < actual_args->p; j++)
    {   
        actual_args->res += actual_args->row[j]*actual_args->col[j];
        /*pthread_mutex_lock(&mutex);
        printf("%d * ", actual_args->row[j]);
        printf("%d = ", actual_args->col[j]);
        printf("%d\n", actual_args->res);
        pthread_mutex_unlock(&mutex);*/
    }
    global = actual_args->res;
    }

int main() {

	unsigned short i, j, n, k;
    time_t rawtime1;
    time_t rawtime2;
    struct timespec spec;

    printf("Matrix Thread: \n");
    printf("Enter the dimension of the matrix: ");
    scanf("%hu", &n);
    int matrix1[n][n];
    int matrix2[n][n];
    int result[n][n];
    struct arguments *args = (struct arguments *)malloc(sizeof(struct arguments) * 2);
    args->p = n;
    for(i = 0; i < n;i++) {
    	for(j = 0; j < n;j++) {
            /*srand(time(0));*/
            matrix1[i][j] = rand()%100;
            matrix2[i][j] = rand()%100;
            result[i][j] = 0;
            args->res = 0;
    	}
    }
    

    clock_gettime(CLOCK_REALTIME, &spec);
    rawtime1  = spec.tv_sec;
    pthread_t threads[n*n];
    args->p = n;
    int num_of_threads = 0;
    for (i = 0; i < n; i++){
        for(int p=0;p<n;p++){
            args->row[p] = matrix1[i][p];
        }
        for (int r = 0; r < n; r++){    
            for(int q=0;q < n;q++){
                args->col[q] = matrix2[q][r];
            }
            /*printf("%d ", args->row[0]);
            printf("%d\n", args->row[1]);
            printf("%d ", args->col[0]);
            printf("%d\n", args->col[1]);*/
            pthread_create(&threads[num_of_threads], NULL, multiply, args);
            result[i][r] = global;
            num_of_threads++;
        }
    }

    for(int q=0 ;q < num_of_threads-1;q++){
        pthread_join(threads[q], NULL);
    }

    clock_gettime(CLOCK_REALTIME, &spec);
    rawtime2  = spec.tv_sec;
    
    for(i = 0; i < n;i++) {
        for(j = 0; j < n;j++) {
            printf("%d ", matrix1[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(i = 0; i < n;i++) {
        for(j = 0; j < n;j++) {
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(i = 0; i < n;i++) {
        for(j = 0; j < n;j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
	return 0;
}