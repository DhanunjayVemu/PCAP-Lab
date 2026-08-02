/*1. Implement an OpenMP program using the parallel for work-sharing construct to perform 
the addition of two matrices of size M×N. Display the resultant matrix and the Thread ID
 responsible for computing each row. Compare the execution time of the serial and parallel
  implementations and comment on the distribution of loop iterations among the threads.*/

#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

int main(){

    int m , n;
    printf("Enter size of the matrix:\n");
    scanf("%d %d",&m, &n);
    
    int **A = (int **)malloc(m* sizeof(int *));
    for(int i=0;i<m;i++){
        A[i]=(int *) malloc(n* sizeof(int));
    }
  
    int **B = (int **)malloc(m*sizeof(int *));
    for(int i=0;i<m;i++){
        B[i]=(int *)malloc(n*sizeof(int));
    } 

    int **C = (int **)malloc(m*sizeof(int *));
    for(int i=0;i<m;i++){
        C[i]=(int *)malloc(n*sizeof(int));
    } 

    //input matrices
    printf("Enter matrix A:\n");
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&A[i][j]);
        }
    }

    printf("Enter matrix B:\n");
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&B[i][j]);
        }
    }

    //serial addition
    double serial_start_time=omp_get_wtime();    
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            C[i][j]=A[i][j]+B[i][j];
        }
    }
    double serial_end_time=omp_get_wtime();
    double serial_time=serial_end_time-serial_start_time;

    //parallel addition
    double parallel_time;
    double parallel_start_time=omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp for
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                C[i][j]=A[i][j]+B[i][j];
            }
            printf(" Row-%d => Thread-%d\n",i,omp_get_thread_num());
            
        }
    }
    double parallel_end_time=omp_get_wtime();
    parallel_time=parallel_end_time-parallel_start_time;

    printf("Resultant:\n");
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            printf("%d\t", C[i][j]);
        }
        printf("\n");
    }

    printf("Serial execution time = %f\n",serial_time);
    printf("Parallel execution time = %f\n",parallel_time);

    
}