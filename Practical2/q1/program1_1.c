#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// global variables
int m , n ,part_size ,i,index_adjuster=0 ;//, output_index=0;
int array[100] , output_array[100];
// int parts_indexes[] =  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ;
/*
proper functions from GfG; Used for sorting 
*/
// swap function (usses in bubble sort):
void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }
}
 
/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
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


    // fork and sort each process: -------------------------------------------------------------------
    for (i=0 ; i<m ; i++){
        int p_id = vfork();
        printf("forkeded ,  i: %d\t p id:%d\n" , i , getpid());
        if (p_id ==0){
            printf("* in child process id: %d\t parent id:%d\n" ,getpid() , getppid()) ;            //for monitoring
            int ii, j;
            for (ii = 0; ii < part_size- 1; ii++)
                for (j = 0; j < part_size- ii - 1; j++)
                    if (array[j +index_adjuster ] > array[j +index_adjuster + 1])
                        swap(&array[j+index_adjuster ], &array[j +index_adjuster + 1]);
        index_adjuster+=part_size;
        exit(0) ; 
        }
        else if (p_id >0 ){
            printf("$ in parent process process id:%d(going to do nothing!)\n" , getpid() ) ;       //for monitoring
            continue;
        }
    }
    printf("array before mergesort and after got sort in seperated parts:\n");                      //for monitorings
    printArray(array  , n);


    // sort array using all sorted parts(using merge sort which its code is from GfG:------------------
    mergeSort(array ,0 ,n-1) ;
    printf("sorted array is:\n");                                                                  
    printArray(array  , n);
    printf("\n") ;
}




// shitty comments:


    // output_array [0] = 0 ;                           //check if swap function works  
    // output_array[1 ]= 1;
    // swap(&output_array[0] , &output_array[1]);
    // printf("%d %d\n" , output_array[0] , output_array[1]); 
    
    