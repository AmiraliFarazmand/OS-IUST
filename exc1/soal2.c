//header files
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

//global variables
int nums[50] , max_sum ,tn=-1;

void push_num(int n)
{
    nums[++tn]=n;
}

int eval(char exp[20])
{
    int i,num,output,r;
    char c;
    for(i=0;exp[i]!='\0';i++)
    {
        c = exp[i];
        
        if(isdigit(c)!=0)
        {
            num = 0;
            int negative_flag = 0 ; 
            while (isdigit(c) || c == '-')
            {
                if (c =='-')
                    negative_flag =1 ;
                num = num*10 + (c-'0');
                i++;
                if(i <strlen(exp))
                    c = exp[i];
                else
                    break;
            }
            i--;
            if (negative_flag==0)
                push_num(num);
            else    
                push_num(num * (-1)) ; 
        }
        else
            continue;
    }
}
        
//main function
int main(int argc, char** argv)
{
    int res[40] ,n , i=0;
    char exp [40] ;
    int n ; 
    scanf("%d" , n);
    scanf("%s" , exp);
    res[i] = eval(exp);


}