#include <stdio.h>
#include <omp.h>

int main()
{
    int n, threads;
    long long fact;
    double start, end;

    printf("Enter N: ");
    scanf("%d", &n);

    printf("Enter number of threads: ");
    scanf("%d", &threads);

    omp_set_num_threads(threads);

    // ==================== CRITICAL ====================
    fact = 1;

    start = omp_get_wtime();

    #pragma omp parallel for
    for(int i = 1; i <= n; i++)
    {
        #pragma omp critical
        {
            fact *= i;
        }
    }

    end = omp_get_wtime();

    printf("\n===== CRITICAL =====\n");
    printf("Factorial = %lld\n", fact);
    printf("Execution Time = %f seconds\n", end - start);

    // ==================== ATOMIC ====================
    // Atomic cannot be used for multiplication (*=)
    printf("\n===== ATOMIC =====\n");
    printf("Atomic cannot be used for factorial because\n");
    printf("#pragma omp atomic supports simple memory updates,\n");
    printf("not operations like fact *= i.\n");

    // ==================== REDUCTION ====================
    fact = 1;

    start = omp_get_wtime();

    #pragma omp parallel for reduction(*:fact)
    for(int i = 1; i <= n; i++)
    {
        fact *= i;
    }

    end = omp_get_wtime();

    printf("\n===== REDUCTION =====\n");
    printf("Factorial = %lld\n", fact);
    printf("Execution Time = %f seconds\n", end - start);

    // ==================== MASTER ====================
    fact = 1;

    start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp master
        {
            for(int i = 1; i <= n; i++)
            {
                fact *= i;
            }
        }
    }

    end = omp_get_wtime();

    printf("\n===== MASTER =====\n");
    printf("Factorial = %lld\n", fact);
    printf("Execution Time = %f seconds\n", end - start);

    // ==================== LOCK ====================
    fact = 1;

    omp_lock_t lock;
    omp_init_lock(&lock);

    start = omp_get_wtime();

    #pragma omp parallel for
    for(int i = 1; i <= n; i++)
    {
        omp_set_lock(&lock);

        fact *= i;

        omp_unset_lock(&lock);
    }

    end = omp_get_wtime();

    omp_destroy_lock(&lock);

    printf("\n===== LOCK =====\n");
    printf("Factorial = %lld\n", fact);
    printf("Execution Time = %f seconds\n", end - start);

    return 0;
}