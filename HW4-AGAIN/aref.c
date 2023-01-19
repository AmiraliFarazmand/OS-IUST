#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>


#define buffSize 32

int main(int argc, char const *argv[])
{
    int pipefd[2], pid;
    char buff1[buffSize]; //buffer for writing
    char buff2[buffSize]; //buffer for reading
    char* msgs[4] = {"hello1" , "hello2" , "hello3" , "hello4"} ; 
    pipe(pipefd);
    for(int i=0;i<4;i++){
        pid=fork();
       
        if (pid == 0) {

           int mypid = getpid();
           sprintf(buff1,"This is number %d log producer",mypid);
        //    sprintf(buff1,"This is number %s log producer",msgs[i]);
            write(pipefd[1], buff1, buffSize);
            exit(EXIT_SUCCESS);
        }
       
    }

    if(pid>0){
        // wait(NULL); //wait for child to finish ;)
        int j=4;
        while(j>0){    
            int Temp= read(pipefd[0], buff2, buffSize);
            printf("log is printing: %s\n",buff2);
            j--;
        }
        
    }
    
}
