#include <stdio.h>
#include <omp.h>

int isPrime(int n)
{
    if (n < 2)
        return 0;

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return 0;
    }

    return 1;
}

int main()
{
    int N;
    int primeCount;
    double start, end;

    printf("Enter the value of N: ");
    scanf("%d", &N);

    //static
    printf("\n==== STATIC SCHEDULING ====\n");

    primeCount = 0;
    start = omp_get_wtime();

    #pragma omp parallel for schedule(static) reduction(+:primeCount)
    for (int i = 1; i <= N; i++)
    {
        printf("Thread %d processed %d\n",
               omp_get_thread_num(), i);

        if (isPrime(i))
            primeCount++;
    }

    end = omp_get_wtime();

    printf("Total Prime Numbers = %d\n", primeCount);
    printf("Execution Time = %f seconds\n\n", end - start);

    //dynamic
    printf("==== DYNAMIC SCHEDULING ====\n");

    primeCount = 0;
    start = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic) reduction(+:primeCount)
    for (int i = 1; i <= N; i++)
    {
        printf("Thread %d processed %d\n",
               omp_get_thread_num(), i);

        if (isPrime(i))
            primeCount++;
    }

    end = omp_get_wtime();

    printf("Total Prime Numbers = %d\n", primeCount);
    printf("Execution Time = %f seconds\n\n", end - start);

    // guided
    printf("==== GUIDED SCHEDULING ====\n");

    primeCount = 0;
    start = omp_get_wtime();

    #pragma omp parallel for schedule(guided) reduction(+:primeCount)
    for (int i = 1; i <= N; i++)
    {
        printf("Thread %d processed %d\n",
               omp_get_thread_num(), i);

        if (isPrime(i))
            primeCount++;
    }

    end = omp_get_wtime();

    printf("Total Prime Numbers = %d\n", primeCount);
    printf("Execution Time = %f seconds\n", end - start);

    return 0;
}