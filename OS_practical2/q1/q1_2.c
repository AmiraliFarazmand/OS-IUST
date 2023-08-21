#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>

// global variables
int m , n ,part_size ,i,index_adjuster=0 , output_index=0;
int array[100] , output_array[100];
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
void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}
void sort_part(int array[]){
        // printf("forkeded ,  i: %d\t p id:%d\n" , i , getpid());                                     //for monitoring
            // printf("* in child process id: %d\t parent id:%d\n" ,getpid() , getppid()) ;            //for monitoring
            int ii, j;
            for (ii = 0; ii < part_size- 1; ii++)
                for (j = 0; j < part_size- ii - 1; j++)
                    if (array[j +index_adjuster ] > array[j +index_adjuster + 1])
                        swap(&array[j+index_adjuster ], &array[j +index_adjuster + 1]);
        index_adjuster+=part_size;
        // exit(0) ; 
        // return NULL;
}
// ====================================================================================================
// ====================================================================================================
// ====================================================================================================
// ====================================================================================================
// ====================================================================================================
// ====================================================================================================
// ====================================================================================================
int main()
{
    // getting inputs: -------------------------------------------------------------------------------
    printf("please enter <<n>>:\n");
    scanf("%d" , &n) ;
    printf("please enter <<m>>:\n");
    scanf("%d", &m) ;
    printf("Now, Please enter your array (with size of n):\n") ;
    part_size = n/m ; 
    for (int i=0 ; i<n ; i++)
        scanf("%d" , &array[i]) ;   //get array


    //  Multi threading : -------------------------------------------------------------------------------
    // ??????????????
    pthread_t tid ; 
    for (i = 0 ; i < n ; i++){
        pthread_create(&tid, NULL, sort_part ,array );
    }
    pthread_join(tid, NULL);
    // pthread_t 
    // pthread_exit(NULL); 
    printf("array before mergesort and after got sort in %d parts:\n" , m);                     
    printArray(array  , n);


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

    // printing output_array which is a sorted array -----------------------------------------------------
    printf("array after final merge(sorted):\n");
    printArray(output_array , n);
    printf("\n") ;
}




// shitty comments:


    // output_array [0] = 0 ;                           //check if swap function works  
    // output_array[1 ]= 1;
    // swap(&output_array[0] , &output_array[1]);
    // printf("%d %d\n" , output_array[0] , output_array[1]); 
    
    