/*1. Implement an OpenMP program to determine and display the total number of threads 
 participating in a parallel region using the omp_get_num_threads() runtime function. 
*/

#include<stdio.h>
#include<omp.h>

int main(){ 
    int total=0;
    #pragma omp parallel
    {
        total=omp_get_num_threads();
        int id=omp_get_thread_num();

        printf("Thread - %d\n",id);

    }
    printf("Total Number of threads: %d\n", total);
}

