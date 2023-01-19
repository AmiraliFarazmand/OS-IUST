// Merge sort code was from practical hw #2

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <limits.h>

#include <errno.h>

// global variables
int m , n ,part_size ,i,index_adjuster=0 , output_index=0;
// int* array;
int output_array[100];
int parts_indexes[] =  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,} ;
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
    // printf("please enter <<n>> (size of array):\n");
    // scanf("%d" , &n) ;
    // printf("please enter <<m>>:\n");
    // scanf("%d", &m) ;
    n = 6 ;
    m = 1 ;
    
    int* array = (int*) mmap(NULL, sizeof(int)* m , PROT_READ| PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    part_size = n/m ; 
    printf("enter your array (with size of %d):\n" ,n) ;
    for (int i=0 ; i<n ; i++)
        scanf("%d" , &array[i]) ;   //get array
    // array = { 4, 1 , 5 , 2 ,3 , 6 } ; 

    // fork and sort each process: -------------------------------------------------------------------
    for (i=0 ; i<m ; i++){
        int p_id = fork();
        if (p_id ==0){
            int ii, j;
            for (ii = 0; ii < part_size- 1; ii++)
                for (j = 0; j < part_size- ii - 1; j++)
                    if (array[j +index_adjuster ] > array[j +index_adjuster + 1])
                        swap(&array[j+index_adjuster ], &array[j +index_adjuster + 1]);
        index_adjuster+=part_size;
        exit(0) ; 
        }
        else if (p_id >0 ){
            // wait(NULL); 
            continue;
        
        }
    }

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
                    // swap(&array[part*part_size +parts_indexes[part]], &array[
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
    printArray(array , n);
    printArray(output_array , n);
    printf("\n") ;
}
