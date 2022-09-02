#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#define PROCNAME "parallel-sum-fork"

int main() {
	unsigned short i, j, k, n;
    
    struct timespec spec;

    printf("Matrix Process: \n");
    printf("Enter the dimension of the matrix: ");
    scanf("%hu", &n);
    int matrix1[n][n];
    int matrix2[n][n];
    int result[n][n];
    FILE* res = fopen("Mat_R.txt", "w");
    pid_t pids[n];
    char buffer[100000];
    char str[100001] = {'\0'};
    srand(time(0));

    for(i = 0; i < n;i++) {
    	for(j = 0; j < n;j++) {
            matrix1[i][j] = rand()%10;
            matrix2[i][j] = rand()%10;
            result[i][j] = 0;
    	}
    }

    clock_t begin = clock();

    for(i = 0; i < n; i++)
    {
        pids[i] = fork();
        if(pids[i] < 0)
        {
            fprintf(stderr, "Error creating subprocess");
        }
        else if(pids[i] == 0) //children's work
        {
            res = fopen("Mat_R.txt", "a+");
            for(j = 0; j < n; j++) {
                for(k = 0; k < n; k++) {
                    result[i][j] += matrix1[i][k]*matrix2[k][j];
                }
                fprintf(res, "%d\t", result[i][j]);
            }
            fprintf(res, "\n");
            exit(0);
        }
    }
    //parent's work
    int status;
    pid_t pid;
    while (n > 0) {
        pid = wait(&status);
        i = n-1;
        --n;
    }
    clock_t end = clock();
    double time = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f nanoseconds\n", time);
    return 0;
}