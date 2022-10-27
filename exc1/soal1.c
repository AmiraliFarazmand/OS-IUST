//header files
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<float.h>

// global variables 
char people[100];
float balance[100];

// function that finds out the index 
int find_index(char name )
{
    // int arrLen = sizeof (name) / sizeof (name[0]);
    // for (int i = 0; i < arrLen; i++){
    //     if (people[i] == name)
    //         return i;
    // }
    return -5 ;
}

int main ()
{
    int n = 0;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%s", people[i]);
    }

    return 0;
}
