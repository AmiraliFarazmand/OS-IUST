#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <limits.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#define ARRAY_SIZE 4

int* arr ;
     
int * shm ;
int  shm_seg ;
int temp_arr[256] ;

void merge_sort(int l , int r){
    if (l<r){
    // int middle = l+ (r-l)/2 ;
    int middle = (l+r)/2;
    merge_sort(l, middle);
    merge_sort(middle+1, r);
    merge(l , middle , middle+1 , r);
    printf("merge_sort called with:(%d , %d)\n" , l,r);
    printArray(arr , ARRAY_SIZE );
    printf("\n***\n");
    }
}

void merge(int s1 , int e1 , int s2 , int e2) {
    int i1=s1; 
    int i2=s2;
    // int n1 = e1-s1+1 ; 
    // int n2 = e2-s2+1 ;
    int k =s1;
    printf("merge func with (%d,%d,%d,%d)\n" , s1, e1, s2,e2) ;
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
    while(i1<e1){
        temp_arr[k] = arr[i1];
        i1++;
        k++;
    }
    while(i2<e2){
        temp_arr[k] = arr[i2];
        i2++;
        k++;     
    }
    for (int tmp_i= s1 ; tmp_i <= k ; tmp_i++){
        arr[tmp_i] = temp_arr[tmp_i];
    }
    printArray(arr, ARRAY_SIZE);
}

void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void main(){
    arr = (int*) mmap(NULL, sizeof(int)* 4, PROT_READ| PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    for (int ii =0; ii<ARRAY_SIZE+1 ; ii++)
        scanf("%d", &arr[ii]);

    merge_sort(0 , ARRAY_SIZE-1);
    // printf("passed 78\n");
    // for (int ii = 0; ii < ARRAY_SIZE ; ii++){
    //     printf("%d\t",arr[ii]);
    // }
    printArray(arr, ARRAY_SIZE);
}