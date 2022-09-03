#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main () {
   char command[50];
   int n = 99;
   while(n>-1){
      //Execute command
      strcpy( command, "./MatrixP" );
      system(command);
      //Renaming the file
      strcpy( command, "Mat_" );
      char* nu;
      asprintf(&nu, "%d", n);
      strcat(command, nu);
      strcat(command, ".txt");
      printf("%s\n",command);
      int name = rename("Mat_R.txt", "Mat_R.txt");
      n--;
   }
   return(0);
} 