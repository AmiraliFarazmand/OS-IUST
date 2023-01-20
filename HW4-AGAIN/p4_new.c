/*
Nokat:
    ba avaz kardane ARRAY_SIZE dar khode code size aaraye ro moshakhas  mikonin.
    aaraye az dakhele console gerefte mishavad az user 
    comment haye dakhele bakhsh haye mokhtalef mitunan tu darke code komak konan
*/

/*
Some useful links:
    https://linuxhint.com/using_mmap_function_linux/#:~:text=The%20mmap()%20function%20is,an%20array%20in%20the%20program.
    https://users.cs.cf.ac.uk/Dave.Marshall/C/node27.html
    https://stackoverflow.com/questions/5656530/how-to-use-shared-memory-with-linux-in-c
    https://man7.org/linux/man-pages/man3/shmat.3p.html
    https://www.geeksforgeeks.org/c-program-for-merge-sort/
    https://github.com/cave7/sort/blob/master/mergesort.c
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <limits.h>
#include <sys/wait.h>


#define ARRAY_SIZE 8

     
int temp_arr[200] ;
void merge_sort(int arr[] , int l , int r);
void merge(int arr[], int s1 , int e1 , int e2) ;
void printArray(int A[], int size);


//=======================================================================================
void main(){
    int* arr = (int*) mmap(NULL, sizeof(int)* ARRAY_SIZE, PROT_READ| PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int pid,pid2;
    int wait1,wait2;
    int mid =( ARRAY_SIZE-1) /2;
    int end = ARRAY_SIZE - 1;
    // arr [ARRAY_SIZE] = {4, 2 , 3, 2 , 0 ,9} ;
    printf("enter your array (with size of %d):\n" ,ARRAY_SIZE) ;
    for (int i=0 ; i<ARRAY_SIZE ; i++)
        scanf("%d" , &arr[i]) ;   //get array
 
    // merge_sort(0 , ARRAY_SIZE-1);
    // for (int i = 0; i < ARRAY_SIZE; i++)
    //     printf("%d\t" , arr[i]);

    pid = fork();
    if (pid ==0){    // merge first half of array in this child process
        merge_sort(arr, 0, mid );
        // printf("$end of child1\n");
        }

    else{
        pid2 = fork();
        if ( pid2 == 0){ //merge second half of array in this child process 
            merge_sort(arr, mid+1 , end);
            // printf("$end of child1\n")
        }
        else{  // wait for its children proccesses and then merge two sorted parts together
            // printf("$parent started\n");
            waitpid(pid,&wait1, 0);
            waitpid(pid2, &wait2, 0);
            // printf("parent ended!");
            merge(arr, 0 , mid , end);
            printf("$$$ sorted array: $$$\n");
            for (int i=0; i<ARRAY_SIZE;i++)
                printf("%d\t" , arr[i]);
            printf("\n");
        }

    }



}
//=================================================================================================
// ------------------------------------------------------------------------------------------------
void merge_sort(int arr[] ,int l , int r){
    if (l<r){
    int middle = l+ (r-l)/2 ;
    merge_sort(arr, l, middle);
    merge_sort(arr, middle+1, r);
    merge(arr, l , middle  , r);
    }
    // printf("merge_sort called with:(%d , %d)\n" , l,r);
    // printf("***\t");
    // for (int ii = 0; ii < ARRAY_SIZE ; ii++) printf("%d\t",arr[ii]);
    // printf("\n");
}
//------------------------------------------------------------------------------------------------
void merge(int arr[] , int s1 , int e1 , int e2) {
    int s2= e1+1;
    int i1=s1; 
    int i2=s2;
    // int n1 = e1-s1+1 ; 
    // int n2 = e2-s2+1 ;
    int k =s1;
    while(i1<=e1 && i2<=e2){
        if (arr[i1]<= arr[i2]){
            temp_arr[k] = arr[i1];
            i1++;
        }
        else{
            temp_arr[k] = arr[i2];
            i2++;
        }
        k++ ;
    }
    while(i1<=e1){
        temp_arr[k] = arr[i1];
        i1++;
        k++;
    }
    while(i2<=e2){
        temp_arr[k] = arr[i2];
        i2++;
        k++;     
    }
    for (int tmp_i= s1 ; tmp_i < k ; tmp_i++){
        arr[tmp_i] = temp_arr[tmp_i];
        // printf("-> %d\n" , arr[tmp_i]);
    }
    // printf("merge called with (%d,%d,%d,%d) and k is:%d\n" , s1, e1, s2, e2 , k) ;
    // printf("###\t");
    // printArray(arr, ARRAY_SIZE);
    // for (int ii = 0; ii < ARRAY_SIZE ; ii++) printf("%d\t",arr[ii]);
    // printf("\n");
}

void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

