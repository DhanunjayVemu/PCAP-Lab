/*3. Implement an OpenMP program to initialize all elements of a 5 × 5 matrix with consecutive 
integers inside a parallel region using the parallel directive. Display the initialized matrix 
and print the Thread ID responsible for initializing each row. */

#include<stdio.h>
#include<omp.h>

int main(){
    int matrix[5][5];
    
    #pragma omp parallel for
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                matrix[i][j]=(i*5)+j+1;
            }
            printf("Row - %d => Thread - %d\n", i,omp_get_thread_num());
        }

    printf("MATRIX: \n");
    for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                printf("%d\t",matrix[i][j]);
            } 
            printf("\n");
        }

    return 0;
}