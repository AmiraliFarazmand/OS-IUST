//header files
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

//global variables
int numbers[50],tn=-1,to=-1;
char op[50];

//function to push numbers
void push_num(int n)
{
    // printf("->push num:%d\n",n);
    numbers[++tn]=n;
}
//function to push operators
void push_op(char ch)
{
    // printf("->push op:%c\n",ch);
    op[++to]=ch;
}
//function to pop nnumbers
int pop_num()
{
    // printf("<-pop num:%d\n",numbers[tn-1] );
    return numbers[tn--];
}
//function to pop operators
char pop_op()
{
    // printf("<-pop op:%c\n",op[to-1]);
    return op[to--];
}
//evaluating the expression
int infix_eval(int numbers[50],char op[50])
{
    int x,y;
    char ope;
    //taking first two operands
    x=pop_num();
    y=pop_num();
    //taking the operator between them
    ope=pop_op();
    //executing the operation
    switch(ope)
    {
        case ',':
            return x+y;
        case '-':
            return y-x;
        case '*':
            return x*y;
        case '/':
            return y/x;
        case '{':
            printf("{ was seen !\n") ; 
            push_num(y);
            return x ;
    }
    return 0;
}
//function to check whether the character is an operator or not
int is_operator(char ch)
{
    return(ch==','||ch=='-'||ch=='*'||ch=='/');
}
//function that declear the precedence of operators
int precedence(char c)
{
    switch(c)
    {
        case ',':
        return 1;
        case '-':
        return 1;
        case '*':
        return 2;
        case '/':
        return 2;
        default:
        return 0;
    }
}
//function to evaluate an infix expression
int eval(char exp[20])
{
    int i,num,output,r;
    char c;
    for(i=0;exp[i]!='\0';i++)
    {
        c = exp[i];
        
        if (c== ' ' ||isspace(c)==1){
            // printf("decleared whitespace\n");
            continue;
        }
        if(isdigit(c)!=0)
        {
            num = 0;
            while (isdigit(c))
            {
                num = num*10 + (c-'0');
                i++;
                if(i <strlen(exp))
                    c = exp[i];
                else
                    break;
            }
            i--;
            push_num(num);
            // printf("______num:%d was here\n" , num);
        }
        
        else if(c=='{')
        {
            push_op(c);
            continue;
            // printf("______{ was here\n");
        }

        else if(c=='}')
        {
            int more_than_one_flag = 0 ; 
            // printf("______} was here\n");
            while(op[to]!='{' )
            {
                more_than_one_flag =1 ; 
                r = infix_eval(numbers, op);
                push_num(r);
            }
            if (more_than_one_flag ==0){
                r = pop_num() ;
                push_num(r) ;
            }
            // r = infix_eval(numbers, op);
            // push_num(r);
            pop_op();
            // printf("****************r: %d\n" , r);
            printf("%d\n" , r);
            // printf("***r:%d\t%d\n"  ,r , numbers[tn--]);
        }
        // the current character is operator for sure
        else if(is_operator(c))
        {
            // while(to!=-1 && precedence(c)<=precedence(op[to]))
            // {
            //     output = infix_eval(numbers, op);
            //     push_num(output);
            // }
            push_op(c);
            // printf("______op:%c was here\n", c);

        }

    }
    //if there\n is any remaining expression, evaluate them
    while(to!=-1)
    {
        output = infix_eval(numbers, op);
        push_num(output);
    }
    return pop_num();
}
int main()
{   
    int n=1, i, high, aux;
    // char exp[10][50];
    // int res[10];
    char input[50];
    char result[50];

    // }
    // scanf("%s" , input);
    fgets (input, 100, stdin);
    eval(input);
    // for(i=0; i<n; i++){
    //     high = max(res, i, n-1);
    //     aux = res[i];
    //     res[i] = res[high];
    //     res[high] = aux;
    // }
    // for (i=0; i<n; i++){
    //     printf("%d ",res[i]);
    // }
    printf("\n");
    return 1;
}