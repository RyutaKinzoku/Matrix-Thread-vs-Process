#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>


int main() {
	unsigned short i, j, k, n;
    
    struct timespec spec;

    printf("Matrix Process: \n");
    //printf("Enter the dimension of the matrix: ");
    //scanf("%hu", &n);
    n=10;
    int matrix1[n][n];
    int matrix2[n][n];
    int result[n][n];
    FILE* res = fopen("Mat_R.txt", "w");
    pid_t pids[n];
    char buffer[100000];
    char str[100001] = {'\0'};

    unsigned int randval;
    FILE *f;
    for(i = 0; i < n;i++) {
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
    FILE* stats = fopen("Stats.txt", "a+");
    fprintf(stats, "%f\n", time);
    printf("%f nanoseconds\n", time);
    return 0;
}