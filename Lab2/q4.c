#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    int n;

    printf("Enter matrix size: ");
    scanf("%d", &n);

    int A[n][n];
    int B[n];
    int C[n];

    printf("Enter matrix:\n");

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter vector:\n");

    for(int i = 0; i < n; i++)
        scanf("%d", &B[i]);


    double start = omp_get_wtime();

    #pragma omp parallel for
    for(int i = 0; i < n; i++)
    {
        C[i] = 0;

        for(int j = 0; j < n; j++)
        {
            C[i] += A[i][j] * B[j];
        }
    }

    double end = omp_get_wtime();


    printf("Result:\n");

    for(int i = 0; i < n; i++)
        printf("%d\n", C[i]);

    printf("Execution time = %f seconds\n", end - start);

    return 0;
}