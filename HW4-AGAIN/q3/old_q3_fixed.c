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
 

#define MSGSIZE 16

 int main(){
char* messages[4]  = {"message1" ,"message2" ,    "message3" ,    "message4"} ; 
    int fd[2] ;
    pipe(fd) ;
    int pid;
    for (int i=0 ; i<4 ; i++){
        pid = fork();
        // if (pid < 0){
        //     printf("Error occurred.");
        //     exit(1);
        // }
        if(pid == 0){
            sprintf (messages , "salam") ; 
            write(fd[1] , messages[i] , MSGSIZE);
            exit(EXIT_SUCCESS);
        }


    }

    // wait(NULL);
    // int i =0;
    if (pid>0){

    for(int j =0 ; j<4 ; j++){
        char* msg;
        read(fd[0] , msg , MSGSIZE);
        printf("%s \n",msg);
        // printf("%s" , msg);
    }
    }


 }