#include <stdio.h>
#include <omp.h>

int main()
{
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter %d elements (0-9):\n", n);
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int seqHist[10] = {0};
    int parHist[10] = {0};

    double start, end;
    double seqTime, parTime;

    // Sequential Histogram
    start = omp_get_wtime();

    for(int i = 0; i < n; i++)
    {
        seqHist[arr[i]]++;
    }

    end = omp_get_wtime();
    seqTime = end - start;

    // Parallel Histogram
    start = omp_get_wtime();

    #pragma omp parallel for
    for(int i = 0; i < n; i++)
    {
        #pragma omp atomic
        parHist[arr[i]]++;
    }

    end = omp_get_wtime();
    parTime = end - start;

    // Display Sequential Histogram
    printf("\nSequential Histogram:\n");
    for(int i = 0; i < 10; i++)
    {
        printf("%d : %d\n", i, seqHist[i]);
    }

    // Display Parallel Histogram
    printf("\nParallel Histogram:\n");
    for(int i = 0; i < 10; i++)
    {
        printf("%d : %d\n", i, parHist[i]);
    }

    printf("\nSequential Execution Time = %f seconds\n", seqTime);
    printf("Parallel Execution Time   = %f seconds\n", parTime);

    return 0;
}