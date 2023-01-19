/* Merge sort in C */
#include<stdio.h>
#include<stdlib.h>
// #define _GNU_SOURCE
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

// #include <sys/types.h>
// #include <sys/stat.h>
// #include <sys/mman.h> /* mmap() is defined in this header */
// #include <fcntl.h>

// Function to Merge Arrays L and R into A. 
// lefCount = number of elements in L
// rightCount = number of elements in R. 
void Merge(int *A,int *L,int leftCount,int *R,int rightCount) {
	int i,j,k;

	// i - to mark the index of left aubarray (L)
	// j - to mark the index of right sub-raay (R)
	// k - to mark the index of merged subarray (A)
	i = 0; j = 0; k =0;

	while(i<leftCount && j< rightCount) {
		if(L[i]  < R[j]) A[k++] = L[i++];
		else A[k++] = R[j++];
	}
	while(i < leftCount) A[k++] = L[i++];
	while(j < rightCount) A[k++] = R[j++];
}

// Recursive function to sort an array of integers. 
void MergeSort(int *A,int n) {
	int mid,i, *L, *R;
	if(n < 2) return; // base condition. If the array has less than two element, do nothing. 

	mid = n/2;  // find the mid index. 

	// create left and right subarrays
	// mid elements (from index 0 till mid-1) should be part of left sub-array 
	// and (n-mid) elements (from mid to n-1) will be part of right sub-array
	L = (int*)malloc(mid*sizeof(int)); 
	R = (int*)malloc((n- mid)*sizeof(int)); 
	
	for(i = 0;i<mid;i++) L[i] = A[i]; // creating left subarray
	for(i = mid;i<n;i++) R[i-mid] = A[i]; // creating right subarray

	MergeSort(L,mid);  // sorting the left subarray
	MergeSort(R,n-mid);  // sorting the right subarray
	Merge(A,L,mid,R,n-mid);  // Merging L and R into A as sorted list.
        free(L);
        free(R);
}
int* A; 
int main() {
	/* Code to test the MergeSort function. */
    int n = 6 ; 
	
	// int A[] = {6,2,3,1,9,10,15,13,12,17}; // creating an array of integers. 
    A = (int*)mmap(NULL, sizeof(int)*n  , PROT_READ| PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	// A  = {1 , 3 , 5 , 4  , 2  , 25 , 4} ; 


    int i,numberOfElements;
	numberOfElements = sizeof(A)/sizeof(A[0]); 

    for (int i=0 ; i<numberOfElements ; i++)
        scanf("%d" , &A[i]) ;   //get array

    for (int prc = 0 ; prc < 1; prc++){
        int pid = fork() ; 
        if (pid==0){
            
        }
        if (pid>0){
            continue;
        }
    }


	// Calling merge sort to sort the array. 
	MergeSort(A,numberOfElements);

	//printing all elements in the array once its sorted.
	for(i = 0;i < numberOfElements;i++) printf("%d ",A[i]);
	return 0;
}