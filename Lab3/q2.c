#include <stdio.h>
#include <omp.h>

#define SIZE 10

int main()
{
    int arr[SIZE];
    int total_sum = 0;
    int even_count = 0;

    #pragma omp parallel shared(arr, even_count) reduction(+:total_sum)
    {
        // Master
        #pragma omp master
        {
            printf("Master Thread ID: %d\n", omp_get_thread_num());

            for(int i = 0; i < SIZE; i++)
            {
                arr[i] = i + 1;
            }

            printf("Total Threads = %d\n\n", omp_get_num_threads());
        }

        // barrier
        #pragma omp barrier

        int partial_sum = 0;

        // atomic
        #pragma omp for
        for(int i = 0; i < SIZE; i++)
        {
            partial_sum += arr[i];
            total_sum += arr[i];

            if(arr[i] % 2 == 0)
            {
                #pragma omp atomic
                even_count++;
            }
        }

        // critical
        #pragma omp critical
        {
            printf("Thread %d processed partial sum = %d\n",
                   omp_get_thread_num(), partial_sum);
        }

        // Master thread 
        #pragma omp master
        {
            printf("\nFinal Sum = %d\n", total_sum);
            printf("Total Even Numbers = %d\n", even_count);
        }
    }

    return 0;
}