#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h> 
#include <unistd.h>

int main() {

	unsigned short i, j, n;

    printf("Matrix Thread: \n");
    printf("Enter the dimension of the matrix: ");
    scanf("%hu", &n);
    int matrix1[n][n];
    int matrix2[n][n];
    int result[n][n];
    for(i = 0; i < n;i++) {
    	for(j = 0; j < n;j++) {
            matrix1[i][j] = rand()%100;
            matrix2[i][j] = rand()%100;
    	}
    }
    time_t rawtime;
    time ( &rawtime );
    void* multiply(void *arg){
        for(i = 0; i < n;i++) {
    	    for(j = 0; j < n;j++) {
                result[i][j] = matrix1[i][j]*matrix2[j][i];
    	    }
        }    
        return arg;
    }
    pthread_t threads[n];
    for (i = 0; i < n; i++){
        pthread_create(&threads[i], NULL, multiply, NULL);
        pthread_join(threads[i], NULL);
    }
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