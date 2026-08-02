#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    int n;

    printf("Enter vector size: ");
    scanf("%d", &n);

    int *A = malloc(n * sizeof(int));
    int *B = malloc(n * sizeof(int));

    int *add = malloc(n * sizeof(int));
    int *sub = malloc(n * sizeof(int));
    int *mul = malloc(n * sizeof(int));

    // Input
    printf("Enter vector A:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    printf("Enter vector B:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &B[i]);


    // ---------------- SERIAL ----------------

    double serial_start = omp_get_wtime();

    for(int i = 0; i < n; i++)
        add[i] = A[i] + B[i];

    for(int i = 0; i < n; i++)
        sub[i] = A[i] - B[i];

    for(int i = 0; i < n; i++)
        mul[i] = A[i] * B[i];

    double serial_end = omp_get_wtime();

    double serial_time = serial_end - serial_start;


    // ---------------- PARALLEL ----------------

    double parallel_start = omp_get_wtime();

    #pragma omp parallel sections
    {
        // Addition task
        #pragma omp section
        {
            for(int i = 0; i < n; i++)
                add[i] = A[i] + B[i];

            printf("Addition done by Thread-%d\n",
                   omp_get_thread_num());
        }


        // Subtraction task
        #pragma omp section
        {
            for(int i = 0; i < n; i++)
                sub[i] = A[i] - B[i];

            printf("Subtraction done by Thread-%d\n",
                   omp_get_thread_num());
        }


        // Multiplication task
        #pragma omp section
        {
            for(int i = 0; i < n; i++)
                mul[i] = A[i] * B[i];

            printf("Multiplication done by Thread-%d\n",
                   omp_get_thread_num());
        }
    }

    double parallel_end = omp_get_wtime();

    double parallel_time = parallel_end - parallel_start;


    // ---------------- RESULTS ----------------

    printf("\nAddition:\n");
    for(int i = 0; i < n; i++)
        printf("%d ", add[i]);

    printf("\n\nSubtraction:\n");
    for(int i = 0; i < n; i++)
        printf("%d ", sub[i]);

    printf("\n\nMultiplication:\n");
    for(int i = 0; i < n; i++)
        printf("%d ", mul[i]);


    // ---------------- PERFORMANCE ----------------

    double speedup = serial_time / parallel_time;

    int threads = omp_get_max_threads();

    double efficiency = speedup / threads;


    printf("\n\nSerial Time   = %.9f seconds\n",
           serial_time);

    printf("Parallel Time = %.9f seconds\n",
           parallel_time);

    printf("Speedup       = %.4f\n",
           speedup);

    printf("Efficiency    = %.2f%%\n",
           efficiency * 100);


    // Free memory
    free(A);
    free(B);
    free(add);
    free(sub);
    free(mul);

    return 0;
}