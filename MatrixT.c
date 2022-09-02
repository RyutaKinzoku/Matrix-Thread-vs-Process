#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h> 
#include <unistd.h>

int global = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct arguments
{
    int row[825];
    int cols[825][825];
    int p;
    int res[825];
};

struct arguments args;

void* multiply(void *arg){
    struct arguments *actual_args = arg;
    int actual_row = 0;
    for (int j = 0; j < actual_args->p; j++)
    {   
        for (int i = 0; i < actual_args->p; i++){
            actual_args->res[j] += actual_args->row[actual_row]*actual_args->cols[j][actual_row];
            pthread_mutex_lock(&mutex);
            printf("%d ", actual_args->row[actual_row]);
            printf("%d\n", actual_args->cols[j][i]);
            pthread_mutex_unlock(&mutex);
        }
        actual_row++;
    }
    pthread_exit(NULL);
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
    
    args.p = n;
    for(i = 0; i < n;i++) {
    	for(j = 0; j < n;j++) {
            /*srand(time(0));*/
            matrix1[i][j] = rand()%100;
            matrix2[i][j] = rand()%100;
            result[i][j] = 0;
    	}
    }
    

    clock_gettime(CLOCK_REALTIME, &spec);
    rawtime1  = spec.tv_sec;
    pthread_t threads[n];
    args.p = n;
    int num_of_threads = 0;
    for (i = 0; i < n; i++){
        for(int q=0;q < n;q++){
            for(int s=0;s < n;s++){
                args.cols[q][s] = matrix2[s][q];
            }
        }
        for(int p=0;p<n;p++){
            args.row[p] = matrix1[i][p];
            printf("%d",args.row[p]);
        }
        printf("\n");
        pthread_create(&threads[i], NULL, multiply, &args);
        result[i][i] = global;
    }
    for(int q=0 ;q < n;q++){
        pthread_join(threads[q], NULL);
    }
    /*
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
    }*/
	return 0;
}