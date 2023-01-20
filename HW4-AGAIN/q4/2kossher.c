/*
Useful links:
    https://users.cs.cf.ac.uk/Dave.Marshall/C/node27.html
    https://stackoverflow.com/questions/5656530/how-to-use-shared-memory-with-linux-in-c
    https://man7.org/linux/man-pages/man3/shmat.3p.html
    https://www.geeksforgeeks.org/c-program-for-merge-sort/
    https://github.com/cave7/sort/blob/master/mergesort.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/wait.h>
#include <errno.h>
#include <assert.h>
#define ARRAY_SIZE 6

int arr [ARRAY_SIZE] = {4, 2 , 3, 2 , 0 ,9} ;
     
int * shm ;
int  shm_segID ;
int temp_arr[100] ;
void merge_sort(int l , int r);
void merge(int s1 , int e1 , int e2) ;
int jj;


void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}
// -------------------------------------------------------------------------------------------------
// =================================================================================================
void main(){
    // int arr[ARRAY_SIZE]= {0,0,0,0} ;
    // int* arr  =(int*) malloc(ARRAY_SIZE* sizeof(int));
    // arr = (int*) mmap(NULL, sizeof(int)* ARRAY_SIZE, PROT_READ| PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    // if (arr=-1){printf("shit\n");return 1;}
    // printArray(arr, ARRAY_SIZE);
    int pid,pid2;
    int shmid; /* return value from shmget() */ 
    int* shm_atch ; 
    shmid = shmget(0 , 500*sizeof(int) , 0);
    if (shmid < 0){printf("error in shmget()") ; exit(1);}

    int mid =( ARRAY_SIZE-1) /2;
    int end = ARRAY_SIZE - 1;
    pid = fork();
    if (pid ==0){ // merge first half of array in this child process
        shm_atch =  shmat(shmid ,(void*)0,  SHM_RND);
        if (shm_atch < 0){printf("error in shmat() on first fork") ; }
        merge_sort(0, mid );
            for(jj=0; jj<88888;jj++){}
        }

    else{
        pid2 = fork();
        if ( pid2 == 0){ //merge second half of array in this child process 
            
            shm_atch =  shmat(shmid ,(void*)0,  SHM_RND);
            if (shm_atch < 0){printf("error in shmat() on second fork") ; }
            merge_sort(mid+1 , end);
            for(jj=0; jj<8888;jj++){}
        }
        else{  // wait for its children proccesses and then merge two sorted parts together
            // for (int i = 0 ; i<2 ; i++)
            //     wait(NULL);
            waitpid(pid ,0 ,0);
            waitpid(pid2 ,0 ,0);
            printf("resid be in!");
            for(jj=0; jj<8888;jj++){}
            for(jj=0; jj<8888;jj++){}
            merge(0 , mid , end);
        }
            for(jj=0; jj<8888;jj++){}
            for(jj=0; jj<8888;jj++){}
            for(jj=0; jj<8888;jj++){}

    }

    // for (int ii =0; ii<ARRAY_SIZE+1 ; ii++){
    //     scanf("%d", &arr[ii]);
    // }
    // merge_sort(0 , ARRAY_SIZE-1);
    printArray(arr, ARRAY_SIZE);
    for (int ii = 0; ii < ARRAY_SIZE ; ii++){
        printf("%d\t",arr[ii]);
    }
}
//=================================================================================================
// ------------------------------------------------------------------------------------------------
void merge_sort(int l , int r){
    if (l<r){
    int middle = l+ (r-l)/2 ;
    // int middle = (l+r)/2;
    merge_sort(l, middle);
    merge_sort(middle+1, r);
    merge(l , middle  , r);
    }
    printf("merge_sort called with:(%d , %d)\n" , l,r);
    printf("***\t");
    // printArray(arr , ARRAY_SIZE );
    for (int ii = 0; ii < ARRAY_SIZE ; ii++) printf("%d\t",arr[ii]);
    printf("\n");
}
//------------------------------------------------------------------------------------------------
void merge(int s1 , int e1 , int e2) {
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
        printf("-> %d\n" , arr[tmp_i]);
    }
    printf("merge called with (%d,%d,%d,%d) and k is:%d\n" , s1, e1, s2, e2 , k) ;
    printf("###\t");
    // printArray(arr, ARRAY_SIZE);
    for (int ii = 0; ii < ARRAY_SIZE ; ii++) printf("%d\t",arr[ii]);
    printf("\n");
}
