
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>


int main(int argc, char **argv)
{
        int pid = fork() ; 
        if (pid==0){
            // char *args[]={"cat" ,argv[1],NULL};
            // execvp(args[0],args);
            // char* args = "cat " ;
            // argv[1];

            char arg1[100] ="cat ";
            strcat(arg1, argv[1]);
            printf("**|%s|\n" , arg1);
            system(arg1) ; 
            // exit(0);
        }
        if (pid>0){
            wait(NULL);
            printf("parent is not working for sure!\n");
        }
    return 0;
}