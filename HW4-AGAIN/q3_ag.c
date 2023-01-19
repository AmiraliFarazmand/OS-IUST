/*
Useful link:
    https://www.geeksforgeeks.org/pipe-system-call/
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h> 

#define MSGSIZE 16

 int main(){
char* messages[4]  = {"message1" ,"message2" ,    "message3" ,    "message4"} ; 
    int fd[2] ;
    pipe(fd) ;
    int pid ; 
    for (int i=0 ; i<4 ; i++){
        pid = fork();
        // if (pid < 0){
        //     printf("Error occurred.");
        //     exit(1);
        // }
        if(pid == 0){
            write(fd[1] , messages[i] , MSGSIZE);
            close(fd[1]);
            exit(EXIT_SUCCESS);
        }


    }
    // if (pid>0){
    {
        // wait(NULL);
        for(int j =0 ; j<4 ; j++){
            char* msg;

            int t= read(fd[0] , msg , MSGSIZE);
            
            printf("%s \n",msg);
            // printf("%s" , msg);
        }

    }

 }