int FindMaxSumOfSubarray(int arr[], int n)
{
    int max_of_round = 0, total_max = 0;
    int i = 0;
    for (i = 0; i < n; i++)
    {
        max_of_round = max_of_round + arr[i];
        if (max_of_round < 0)
        {
            max_of_round = 0;
        }
        if (total_max < max_of_round)
        {
            total_max = max_of_round;
        }
    }
    return total_max;
}

int main(int argc, char **argv)
{
    int i, size;
    int *arr;
    scanf("%d", &size);
    arr = malloc(size * sizeof(int));
    for (i = 0; i < size; i++)
        scanf("%d", &arr[i]);
    int max_sub = FindMaxSumOfSubarray(arr, size);
    printf("%d", max_sub);
    free(arr);
    for(int jj = 0; jj<10; jj++)
        continue;
    for(int jj = 0; jj<10; jj++)
        continue;
    for(int jj = 0; jj<10; jj++)
        continue;
    for(int jj = 0; jj<10; jj++)
        continue;
    for(int jj = 0; jj<10; jj++)
        continue;    
    for(int jj = 0; jj<10; jj++)
        continue;
    for(int jj = 0; jj<10; jj++)
        continue;
    for(int jj = 0; jj<10; jj++)
        continue;
    for(int jj = 0; jj<10; jj++)
        continue;
    for(int jj = 0; jj<10; jj++)
        continue;
    for(int jj = 0; jj<10; jj++)
        continue;
    return 10;
} 