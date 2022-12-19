#include <stdio.h>
#include<stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include<math.h>
#include<unistd.h>

#define R_C 2 // number of rows and rows
// changed rslt matrix into a global variable
int rslt[R_C][R_C];






// A function to multiply 2 matrices (Copied from GfG)
void mulMat(int mat1[][R_C], int mat2[][R_C])
{
    printf("Multiplication of given two matrices is:\n");
        for (int i = 0; i < R_C; i++) {
        for (int j = 0; j < R_C; j++) {
            rslt[i][j] = 0;
                        for (int k = 0; k < R_C; k++) {
                rslt[i][j] += mat1[i][k] * mat2[k][j];
            }
                        printf("%d\t", rslt[i][j]);
        }
                printf("\n");
    }
}
// Driver code
int main()
{
    // R_C = 4, R_C = 4 and R_C = 4, R_C = 4 (Update these
    // values in MACROs)
    int mat1[R_C][R_C] = { { 1, 1 },
                        { 1, 2 } };

      // Function call
    mulMat(mat1, mat1);

    return 0;
}
