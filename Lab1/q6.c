/*6. Implement an OpenMP program to compute the sum of elements of a large array in parallel 
using the parallel for directive. Measure and display the execution time of the parallel 
program using the omp_get_wtime() runtime function and compare it with the 
corresponding serial implementation. */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ARRAY_SIZE 50000000 // 50 million elements

int main() {
    // Allocate memory on the heap for the large array
    int *arr = (int *)malloc(ARRAY_SIZE * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Initialize array with sample values
    for (long i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = 1; // Sum should equal ARRAY_SIZE
    }

    double start_time, end_time;
    double serial_time, parallel_time;

    // ==========================================
    // 1. SERIAL IMPLEMENTATION
    // ==========================================
    long long serial_sum = 0;
    
    start_time = omp_get_wtime();
    for (long i = 0; i < ARRAY_SIZE; i++) {
        serial_sum += arr[i];
    }
    end_time = omp_get_wtime();
    serial_time = end_time - start_time;

    // ==========================================
    // 2. PARALLEL IMPLEMENTATION (OpenMP)
    // ==========================================
    long long parallel_sum = 0;

    start_time = omp_get_wtime();
    #pragma omp parallel for reduction(+:parallel_sum) schedule(static)
    for (long i = 0; i < ARRAY_SIZE; i++) {
        parallel_sum += arr[i];
    }
    end_time = omp_get_wtime();
    parallel_time = end_time - start_time;

    // ==========================================
    // RESULTS & PERFORMANCE COMPARISON
    // ==========================================
    printf("--- Array Sum Performance Comparison ---\n");
    printf("Array Size           : %d elements\n", ARRAY_SIZE);
    printf("Threads Used         : %d\n\n", omp_get_max_threads());

    printf("Serial Sum           : %lld\n", serial_sum);
    printf("Serial Time          : %f seconds\n\n", serial_time);

    printf("Parallel Sum         : %lld\n", parallel_sum);
    printf("Parallel Time        : %f seconds\n\n", parallel_time);

    if (parallel_time > 0) {
        printf("Speedup : %.2fx faster\n", serial_time / parallel_time);
    }

    // Free memory
    free(arr);
    return 0;
}