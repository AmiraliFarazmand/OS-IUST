#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <math.h>

#define NUM_PU

// got assisted by:
    // https://github.com/meliiwamd/Operating-System/tree/main/HW4
struct prime {
int value; // value of the prime number
int counter; // a counter to decrement (at the start counter = value)
int proc_unit ;
};

struct prime next_round(struct prime p){
    p.value = p.value + p.proc_unit ;
    
};

struct prime* generate_first100(){
    struct prime* first100_primes = (struct prime*) malloc(100* sizeof(struct prime));
    int num=2,count = 0, is_prime=1 ;
    while (count<=100){
        int k= (int) sqrt(num);
        for (int i=0; i<k ; i++){
            if (num%i==0){
                is_prime=0;
                break ; 
            }
        }
        if(is_prime==1){
            struct prime tmp_prime;
            tmp_prime.proc_unit= num%8 ; 
            tmp_prime.value = num;
            first100_primes[count] = tmp_prime;
            count++;
        }
        is_prime=1; 
        num++;
    }
    return first100_primes;
}


void main(){
    struct prime* first100_primes = generate_first100();
    int fd[2] ; 
    pipe(fd) ; 

    int parsing_child [16] ; 
    for (int i = 0; i < 8 ; i++)    
        pipe(&parsing_child[2*i]);    //create 8 pipe for children to comunicate 

    for (int i = 0; i < 8   ; i++){ // make 8 child to represent 8 
        int pid = fork();
        if (pid<0 ){printf("error occurred on fork()"); exit(EXIT_FAILURE);}
        else if (pid == 0){
            struct prime prime_num ; 
            while(read(parsing_child[i * 2], &prime_num, sizeof(struct prime)) >0){
                if (prime_num.value ==-20 ){break ;}   //it's not  a prime number anymore

                prime_num.value += prime_num.proc_unit ; // this prime number goes to next round 
                prime_num.counter--;
                prime_num.proc_unit = (prime_num.proc_unit+1)%8 ; 

                if(prime_num.counter == 0){     //check if it satisfy the counter==0 then send it to its parent
                    write(fd[1], &prime_num, sizeof(struct prime)); 
                }
                else{   //go to next PU and continue calculating wether it satisfy counter==0 or not
                     write(parsing_child[2 * prime_num.proc_unit + 1], &prime_num, sizeof(struct prime));
                }


            }
            exit(EXIT_SUCCESS);
        }

    }


    for(int i= 0 ; i<100 ; i++){
        struct prime temp_prime ;
        if(read(fd[0], &temp_prime, sizeof(struct prime)) > 0){
            printf("Discovend %d th number prime number, it is : %d\n", i + 1, temp_prime.value);
        }
    }

    for(int i = 0; i < 8; i++){ //kill non prime number
        struct prime tmp = {-20, 0, 0};

        write(parsing_child[i * 2 + 1], &tmp, sizeof(struct prime));

    }


}

