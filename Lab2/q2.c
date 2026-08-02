/*2. Implement an OpenMP program to read a matrix A of size 5 × 5 and produce matrix B according to the specified transformation:

• Principal diagonal = 0
• Elements below the diagonal = maximum value of the corresponding row in A
• Elements above the diagonal = minimum value of the corresponding row in A

Display both matrices and indicate the Thread ID responsible for processing each row.*/

#include <stdio.h>
#include <omp.h>

int main()
{
    int A[5][5];
    int B[5][5];

    // Input matrix A
    printf("Enter 5x5 matrix A:\n");

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }

    #pragma omp parallel for
    for(int i = 0; i < 5; i++)
    {
        int max = A[i][0];
        int min = A[i][0];

        // Find maximum and minimum of current row
        for(int j = 1; j < 5; j++)
        {
            if(A[i][j] > max)
                max = A[i][j];

            if(A[i][j] < min)
                min = A[i][j];
        }

        // Create row of matrix B
        for(int j = 0; j < 5; j++)
        {
            if(i == j)
                B[i][j] = 0;

            else if(i > j)
                B[i][j] = max;

            else
                B[i][j] = min;
        }

        printf("Row-%d => Thread-%d\n",
               i, omp_get_thread_num());
    }

    // Display B
    printf("\nMatrix B:\n");

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            printf("%d\t", B[i][j]);
        }

        printf("\n");
    }

    return 0;
}