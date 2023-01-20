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


int * shm ;
int  shm_seg ;
int my_mergesort(int* a,int len ){
    
    a = (int*) mmap(NULL, sizeof(int)* len , PROT_READ| PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    shm_seg=shmget(IPC_PRIVATE,10000 * 4 , IPC_CREAT|0666);
    shm=shmat(shm_seg,(void *) 0,SHM_RND) ;
    int pid = fork();
    if (pid ==0){
    }







    int step=1;
    int *m1=(int *)malloc(len*sizeof(int));
    if(!m1) return -1;
    int *m2=(int *)malloc(len*sizeof(int));
    if(!m2) return -1;
    while (step<len) {
        int i,s1,e1,s2,e2;
        for(i=0;(i+step-1)<(len-1);i+=2*step){
            s1=i;
            e1=i+step-1;
            s2=e1+1;
            (i+2*step-1)<(len-1)?(e2=i+2*step-1):(e2=len-1);
            merge_two(a,s1,e1,s2,e2,m1,m2);
        }
        step=step<<1;
    }
    return 0;
}

int merge_two(int *a,int s1,int e1,int s2,int e2,int* m1,int* m2){
    int len1=e1-s1+1;
    int len2=e2-s2+1;
    int p1=0;
    int p2=0;
    int p=s1;
    memcpy(m1,a+s1,sizeof(int)*len1);
    memcpy(m2,a+s2,sizeof(int)*len2);
    while (p1<len1&&p2<len2) {
        if(m1[p1]<m2[p2]){
            a[p++]=m1[p1++];
        }
        else{
            a[p++]=m2[p2++];
        }
    }
    while (p1<len1) {
        a[p++]=m1[p1++];
    }
    while(p2<len2){
        a[p++]=m2[p2++];
    }
    return 0;
}


int main(){
    int a[10]={8,9,20,0,3,20,0};
    int len=7;
    my_mergesort(a,len);
    
    int i;
    for (i=0;i<len;i++) {
        printf("%d\t",a[i]);
    }
    printf("\n");
    return 0;
}


