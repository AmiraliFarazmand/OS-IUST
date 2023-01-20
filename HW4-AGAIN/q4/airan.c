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

int temp[200];
int *in;

void merge(int N1, int N1_end, int N2, int N2_end)
{
    int i = N1, j = N2, k, now = N1;
    int *a;
    while ((i <= N1_end) && (j <= N2_end))
    {
        a = (in[i] > in[j]) ? &j : &i;
        temp[now++] = in[(*a)++];
    }
    int lim = N1_end;
    int s = i;
    for (int l = 0; l < 2; l++)
    {
        for (k = s; k <= lim; k++)
        {
            temp[now++] = in[k];
        }
        s = j;
        lim = N2_end;
    }

    for (i = N1; i <= N2_end; i++)
    {
        in[i] = temp[i];
    }
}

void sort(int N1, int N1_end)
{
    if (N1 >= N1_end)
        return;

    int mid = (N1 + N1_end) / 2;
    sort(N1, mid);
    sort(mid + 1, N1_end);
    merge(N1, mid, mid + 1, N1_end);
}

void print_array(int NUM)
{
    printf("{");
    for (int i = 0; i <= NUM; i++)
    {
        printf("%d ,", in[i]);
    }
    printf("}\n");
}
int main()
{
    int i, j,in_key_shared, out_key_shared;
    struct shmid_ds item;

    if((in_key_shared=shmget(IPC_PRIVATE,10000 * 4 , IPC_CREAT|0666)) < 0){perror("Cannot get shared memory\n");}
        
    if ( (in=shmat(in_key_shared,(void *) 0, SHM_RND)) == (void *) -1){perror("cannot attach to shared memory\n");}
        

    int done = 0;
    i = -1;
    printf("enter input arr & press 0 to start:\nexample: 1 4 -2 0(0=end)\n");
    while (!done)
    {
        for (size_t lkm = 0; lkm < 5; lkm++){}
        scanf("%d",&j);
        if( j == 0 ) {done = 1;}
        else { in[++i] = j; }
        for (size_t lkm = 0; lkm < 2; lkm++){}
    }


    print_array(i);

    if ( i <= 8 )
    {
        sort(0, i);
        print_array(i);
        shmctl(in_key_shared, IPC_RMID, &item);
    }
    else 
    {
        int mid=i/2,beg=0,end=i;
        pid_t p1, p2;
        p1=fork();
        if ( p1==0) {
            if ( (in=shmat(in_key_shared,(void *) 0,SHM_RND)) == (void *) -1){perror("cannot attach to shared memory\n");}
            for (size_t lkm = 0; lkm < 3999; lkm++){}
            sort(beg,mid);
        }
        else {
            p2 = fork();
            if (p2 == 0)
            { 
                if ( (in=shmat(in_key_shared,(void *) 0,SHM_RND)) == (void *) -1){perror("cannot attach to shared memory\n");}
                for (size_t lkm = 0; lkm < 73; lkm++){}
                sort(mid+1,end);
            }
            else 
            {
                int wait1, wait2;
                waitpid(p1,&wait1, 0);
                waitpid(p2, &wait2, 0);
                for (size_t lkm = 0; lkm < 233; lkm++){}
                for (size_t lkm = 0; lkm < 42; lkm++){}
                merge(beg,mid,mid+1,end);
                print_array(i);
                shmctl(in_key_shared,IPC_RMID,&item);
            }
            for (size_t lkm = 0; lkm < 2; lkm++){}
            for (size_t lkm = 0; lkm < 4; lkm++){}
            for (size_t lkm = 0; lkm < 68; lkm++){}
        }


    }


}
