// header files
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <float.h>
int main(void)
{
char *people_list[100];
char input[100];
int balance_list[100], balance_list_copy[100], differece_list[100];
int temp_num1, temp_num2, person_index=0 ,i ,j ,k , ii ;
char temp_name[50];
int part = 0, mod_temp;
    // getting names
    int n;
    scanf("%d", &n);
    for ( i = 0; i < n; i++)
    {
        people_list[i] = malloc(200 * sizeof(char));
        scanf("%s", input);
        strcpy(people_list[i], input);
        balance_list[i] = 0;
    }

    // deviding money:
    for ( i = 0; i < n; i++)
    {
        scanf("%s", temp_name);
        scanf("%d %d", &temp_num1, &temp_num2);
        if (temp_num2!=0){
            mod_temp = temp_num1 % temp_num2;
            part = (temp_num1-mod_temp) / temp_num2;
        }
        else if (temp_num2==0){
            mod_temp = temp_num1;
            part =0 ;
        }
        for ( ii = 0; ii <n ;  ii++)
        {
            if (strcmp(temp_name , people_list[ii])==0){person_index = ii;break;}
        }
        for ( j=0;temp_num2>0 && j < temp_num2; j++)
        {
            scanf("%s", input);
            for ( k = 0; k < n; k++)
            {
                if (strcmp(input , people_list[k])==0){
                    balance_list[k] += part;
                    break ; 
                }
            }
        }
            balance_list[person_index] += mod_temp;
            balance_list_copy[person_index] = temp_num1;
    }

    // print difference between people_list and balance_list_copy
    
    for (i = 0; i < n; i++)
    {
        int difference_temp = balance_list[i] - balance_list_copy[i];
        differece_list[i] = difference_temp;
    }
    // printf("nm: last: first: difference:\n");
    for (i = 0; i < n; i++)
    {
        printf("%s %d\n", people_list[i], differece_list[i]);
        // printf("%s %d %d %d\n" , people_list[i] ,balance_list[i] , balance_list_copy[i] , differece_list[i]);
    }  
    // free(people_list);
}
