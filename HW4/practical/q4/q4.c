#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/uio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <semaphore.h>

// global variables
int m , n ,part_size ,i,index_adjuster=0 , output_index=0;
int* array;
int output_array[100];
int parts_indexes[] =  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ;
/*
prepared functions from GfG; Used for sorting 
*/
// swap function (usses in bubble sort):
void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
// function to ptint array
void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}
// ====================================================================================================
int main()
{
    // getting inputs: -------------------------------------------------------------------------------
    printf("please enter <<n>> (size of array):\n");
    scanf("%d" , &n) ;
    // printf("please enter <<m>>:\n");
    // scanf("%d", &m) ;
    m = 2 ;
    printf("Now, Please enter your array (with size of n):\n") ;
    array = (int*) mmap(NULL, sizeof(int)* m , PROT_READ| PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    part_size = n/m ; 
    for (int i=0 ; i<n ; i++)
        scanf("%d" , &array[i]) ;   //get array


    // fork and sort each process: -------------------------------------------------------------------
    for (i=0 ; i<m ; i++){
        int p_id = fork();
        // printf("forkeded ,  i: %d\t p id:%d\n" , i , getpid());                                     //for monitoring
        if (p_id ==0){
            // printf("* in child process id: %d\t parent id:%d\n" ,getpid() , getppid()) ;            //for monitoring
            int ii, j;
            for (ii = 0; ii < part_size- 1; ii++)
                for (j = 0; j < part_size- ii - 1; j++)
                    if (array[j +index_adjuster ] > array[j +index_adjuster + 1])
                        swap(&array[j+index_adjuster ], &array[j +index_adjuster + 1]);
                        printf("swapped%d %d \n" , array[j+index_adjuster] , array[j+index_adjuster + 1]);
        index_adjuster+=part_size;
        exit(0) ; 
        }
        else if (p_id >0 ){
            // printf("$ in parent process process id:%d(going to do nothing!)\n" , getpid() ) ;       //for monitoring
            continue;
        
        }
    }
    printf("array before final merge and after got sort in %d parts:\n" , m);                     
    printArray(array  , n);
    printf("-------------------------------------\n");

    // sort array using all sorted parts:--------------------------------------------------------------
    for (int indx = 0; indx < n; indx++){
        int min = 100000000 ; 
        int temp_index=0 ; 
        for (int part = 0; part < m; part++){
            if(parts_indexes[part]<part_size){
                int tmp_num = array[part*part_size + parts_indexes[part]];
                if (tmp_num <min){
                    min =  tmp_num ; 
                    temp_index = part;
                }
            }
            else{
                continue;
            }    
        }
        output_array[output_index] = min ; 
        output_index++;
        parts_indexes[temp_index]++;

    }
    for (int i =0 ; i < m; i++){
        wait(NULL);
    }// printing output_array which is a sorted array -----------------------------------------------------
    printf("array after final merge(sorted):\n");
    printArray(output_array , n);
    printf("\n") ;
}


