#include <stdio.h>
#include <omp.h>

int main()
{
    int n = 10;
    int sum;

    printf("Sum of first %d natural numbers\n\n", n);

    //shared
    sum = 0;
    printf("1. SHARED\n");

    #pragma omp parallel for shared(sum)
    for(int i = 1; i <= n; i++)
    {
        sum += i;      
    }

    printf("Result = %d\n\n", sum);

    //private
    sum = 0;
    printf("2. PRIVATE\n");

    #pragma omp parallel for private(sum)
    for(int i = 1; i <= n; i++)
    {
        sum += i;
    }

    printf("Result = %d\n\n", sum);

    //firstprivate
    sum = 0;
    printf("3. FIRSTPRIVATE\n");

    #pragma omp parallel for firstprivate(sum)
    for(int i = 1; i <= n; i++)
    {
        sum += i;
    }

    printf("Result = %d\n\n", sum);

    //lastprivate
    sum = 0;
    printf("4. LASTPRIVATE\n");

    #pragma omp parallel for lastprivate(sum)
    for(int i = 1; i <= n; i++)
    {
        sum += i;
    }

    printf("Result = %d\n", sum);

    return 0;
}