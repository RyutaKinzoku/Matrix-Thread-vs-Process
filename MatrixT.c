#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h> 
#include <unistd.h>

int main() {

	unsigned short i, j, n, k;

    printf("Matrix Thread: \n");
    printf("Enter the dimension of the matrix: ");
    scanf("%hu", &n);
    int matrix1[n][n];
    int matrix2[n][n];
    int result[n][n];
    for(i = 0; i < n;i++) {
    	for(j = 0; j < n;j++) {
            srand(time(0));
            matrix1[i][j] = rand()%100;
            matrix2[i][j] = rand()%100;
    	}
    }
    time_t rawtime;
    time ( &rawtime );
    void* multiply(void *arg){
        for(j = 0; j < n; j++) {
                int m = 0;
                for(k = 0; k < n; k++) {
                    m += matrix1[i][k]*matrix2[k][j];
                }
                result[i][j] = m;
            }
        return arg;
    }
    pthread_t threads[n];
    for (i = 0; i < n; i++){
        pthread_create(&threads[i], NULL, multiply, NULL);
        pthread_join(threads[i], NULL);
    }
    time_t rawtime2;
    time ( &rawtime2 );
    /*
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