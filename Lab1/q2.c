/*2. Implement an OpenMP program that creates a user-specified number of threads using the 
omp_set_num_threads() runtime function and displays the Thread ID of each thread.*/

#include<stdio.h>
#include<omp.h>

int main(){

    int num;
    printf("Enter number of threads:\n");
    scanf("%d",&num);
    omp_set_num_threads(num);
    #pragma omp parallel
    {   
        printf("Thread ID - %d\n", omp_get_thread_num());
    }
    return 0;
}