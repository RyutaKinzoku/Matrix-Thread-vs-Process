#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#define PROCNAME "parallel-sum-fork"

int main() {
	unsigned short i, j, k, n, w, dLen;

    printf("Matrix Process: \n");
    printf("Enter the dimension of the matrix: ");
    scanf("%hu", &n);
    int matrix1[n][n];
    int matrix2[n][n];
    int result[n][n];
    pid_t pid;
    int connect[n];
    char buffer[100000];
    char str[100001] = {'\0'};

    for(i = 0; i < n;i++) {
    	for(j = 0; j < n;j++) {
            matrix1[i][j] = rand()%10;
            matrix2[i][j] = rand()%10;
            result[i][j] = 0;
    	}
    }
    time_t rawtime;
    time ( &rawtime );
    for(i = 0; i < n; i++)
    {
        pipe(connect);
        if(connect < 0){
            printf("Error creating pipe");
        }
        pid = fork();
        //printf("PIIIIIIIIIDDDDDD %d %d\n", i, pid);
        if(pid < 0)
        {
            fprintf(stderr, "Error creating subprocess");
        }
        else if(pid==0) //child's work
        {
            for(j = 0; j < n; j++) {
                for(k = 0; k < n; k++) {
                    result[i][j] += matrix1[i][k]*matrix2[k][j];
                }
                //printf("result[%d][%d] %d\n", i, j, result[i][j]);
                int len = sprintf( str, "%d ", result[i][j] );
                w = write( connect[1], str, len );
                if( w != len )
                    printf("\nWrite error");
            }
            *str=0;
            write(connect[1], str, 1);
            exit(0);
        }
        if(pid > 0)//parent's work
        {
            wait(0);
            if( ( dLen = read( connect[0], buffer, sizeof ( buffer ) ) ) <=0 )
            {
                fprintf( stderr,"Read failed: %s\n", strerror( errno ) );
                exit(1);
            }
			sscanf( buffer, "%d %d %d %d", &result[i][0], &result[i][1], &result[i][2], &result[i][3]);
        }
    }
    /*
    printf("\n");
    printf("\n");
    for(i = 0; i < n;i++) {
        for(j = 0; j < n;j++) {
            printf("%d\t", matrix1[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(i = 0; i < n;i++) {
        for(j = 0; j < n;j++) {
            printf("%d\t", matrix2[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(i = 0; i < n;i++) {
        for(j = 0; j < n;j++) {
            printf("%d\t", result[i][j]);
        }
        printf("\n");
    }
    */
    return 0;
}