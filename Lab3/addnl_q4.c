#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main()
{
    long long int totalPoints, insideCircle = 0;
    int threads;

    printf("Enter total number of random points: ");
    scanf("%lld", &totalPoints);

    printf("Enter number of threads: ");
    scanf("%d", &threads);

    omp_set_num_threads(threads);

    double start = omp_get_wtime();

    #pragma omp parallel
    {
        unsigned int seed = time(NULL) + omp_get_thread_num();

        #pragma omp for reduction(+:insideCircle)
        for(long long int i = 0; i < totalPoints; i++)
        {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;

            if((x * x + y * y) <= 1.0)
                insideCircle++;
        }
    }

    double end = omp_get_wtime();

    double pi = 4.0 * insideCircle / totalPoints;

    printf("\nPoints Inside Circle = %lld\n", insideCircle);
    printf("Total Points         = %lld\n", totalPoints);
    printf("Estimated Pi         = %.10f\n", pi);
    printf("Execution Time       = %f seconds\n", end - start);

    return 0;
}