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