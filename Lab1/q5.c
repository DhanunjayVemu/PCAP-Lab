/*5. Implement an OpenMP program to perform the addition of two matrices of size M×N using 
the parallel for directive. Display the resultant matrix and indicate the Thread ID 
responsible for computing each row (or element) of the result. */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int rows, cols;

    printf("Enter matrix dimensions (Rows Columns): ");
    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0) {
        printf("Invalid dimensions!\n");
        return 1;
    }

    // Allocate 1D arrays to represent 2D matrices (Rows x Cols)
    int *A = (int *)malloc(rows * cols * sizeof(int));
    int *B = (int *)malloc(rows * cols * sizeof(int));
    int *C = (int *)malloc(rows * cols * sizeof(int));

    if (!A || !B || !C) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // User Input for Matrix A
    printf("\nEnter elements for Matrix A (%dx%d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("A[%d][%d]: ", i, j);
            scanf("%d", &A[i * cols + j]);
        }
    }

    // User Input for Matrix B
    printf("\nEnter elements for Matrix B (%dx%d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("B[%d][%d]: ", i, j);
            scanf("%d", &B[i * cols + j]);
        }
    }

    printf("\n--- Parallel Matrix Addition ---\n");

    // Compute Matrix C = A + B in parallel by rows
    #pragma omp parallel for 
    for (int i = 0; i < rows; i++) {
        int thread_id = omp_get_thread_num();

        for (int j = 0; j < cols; j++) {
            int idx = i * cols + j;
            C[idx] = A[idx] + B[idx];
        }

        #pragma omp critical
        {
            printf("Row %d computed by Thread %d\n", i, thread_id);
        }
    }

    // Display Resultant Matrix C
    printf("\n--- Resultant Matrix C (%dx%d) ---\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", C[i * cols + j]);
        }
        printf("\n");
    }

    // Free memory
    free(A);
    free(B);
    free(C);

    return 0;
}