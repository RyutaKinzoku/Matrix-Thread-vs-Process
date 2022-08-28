#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	unsigned short i, j, n;

    printf("Matrix Process: \n");
    printf("Enter the dimension of the matrix: ");
    scanf("%hu", &n);
    int matrix1[n][n];
    int matrix2[n][n];
    for(i = 0; i < n;i++) {
    	for(j = 0; j < n;j++) {
            matrix1[i][j] = rand()%100;
            matrix2[i][j] = rand()%100;
    	}
    }
    time_t rawtime;
    time ( &rawtime );
	return 0;
}