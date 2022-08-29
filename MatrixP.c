#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define PROCNAME "parallel-sum-fork"

int main() {
	unsigned short i, j, k, n;

    printf("Matrix Process: \n");
    printf("Enter the dimension of the matrix: ");
    scanf("%hu", &n);
    int matrix1[n][n];
    int matrix2[n][n];
    int result[n][n];
    pid_t pids[n];
    for(i = 0; i < n;i++) {
    	for(j = 0; j < n;j++) {
            matrix1[i][j] = rand()%100;
            matrix2[i][j] = rand()%100;
    	}
    }
    time_t rawtime;
    time ( &rawtime );
    for(i = 0; i < n; i++)
    {
        if(pids[i] != 0){
   	       pids[i] = fork();
        }
        if(pids[i] < 0)
        {
            fprintf(stderr, "Error creating subprocess");
            return 1;
        }
        else if(pids[i]==0) //child's work
        {
            for(j = 0; j < n; j++) {
                int m = 0;
                for(k = 0; k < n; k++) {
                    m += matrix1[i][k]*matrix2[k][j];
                }
                result[i][j] = m;
                //printf("result[%d][%d] %d\n", i, j, result[i][j]);
            }
        }
    }
    //parent's work
    for (i = 0; i < n; ) {
        int status = 0;
        if (pids[i] > 0) {
            wait(0);
            continue;
        }
        ++i;
    }
    /**/
    printf("\n");
    printf("\n");
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
    /**/
	return 0;
}