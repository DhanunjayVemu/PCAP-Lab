#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for(int i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for(int i = 0; i < n2; i++)
        R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;

    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i < n1)
        arr[k++] = L[i++];

    while(j < n2)
        arr[k++] = R[j++];
}

// Sequential Merge Sort
void mergeSort(int arr[], int l, int r)
{
    if(l < r)
    {
        int m = (l + r) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Parallel Merge Sort
void parallelMergeSort(int arr[], int l, int r)
{
    if(l < r)
    {
        int m = (l + r) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, l, m);

            #pragma omp section
            parallelMergeSort(arr, m + 1, r);
        }

        merge(arr, l, m, r);
    }
}

void printArray(int arr[], int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n], arr2[n];

    printf("Enter %d elements:\n", n);

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        arr2[i] = arr[i];
    }

    int threads;

    printf("Enter number of threads: ");
    scanf("%d", &threads);

    omp_set_num_threads(threads);

    // Sequential
    double start = omp_get_wtime();

    mergeSort(arr, 0, n - 1);

    double end = omp_get_wtime();

    double seqTime = end - start;

    // Parallel
    start = omp_get_wtime();

    parallelMergeSort(arr2, 0, n - 1);

    end = omp_get_wtime();

    double parTime = end - start;

    printf("\nSequential Sorted Array:\n");
    printArray(arr, n);

    printf("\nParallel Sorted Array:\n");
    printArray(arr2, n);

    printf("\nSequential Time = %f seconds\n", seqTime);
    printf("Parallel Time   = %f seconds\n", parTime);

    double speedup = seqTime / parTime;
    double efficiency = speedup / threads;

    printf("Speedup         = %f\n", speedup);
    printf("Efficiency      = %f\n", efficiency);

    return 0;
}