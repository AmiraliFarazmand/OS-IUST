
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char **argv)
{
        int pid = fork() ; 
        if (pid==0){
            char *args[]={"cat" ,argv[1],NULL};
            execvp(args[0],args);
        }
        if (pid>0){
            wait(NULL);
            printf("parent is working for sure!\n");
        }
    return 0;
}