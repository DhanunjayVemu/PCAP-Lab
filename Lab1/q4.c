/*4. Implement an OpenMP program to perform the addition of two one-dimensional arrays of 
size N using the parallel for directive. Display the resulting array and identify the Thread 
ID that computes each array element. */

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(){

    int n;
    printf("Enter size of the arrays:\n");
    scanf("%d",&n);
    
    int *arr1=(int*)malloc(n*sizeof(int));
    int *arr2=(int*)malloc(n*sizeof(int));
    int *arr3=(int*)malloc(n*sizeof(int));


    printf("Enter array1: \n");
    for(int i=0;i<n;i++){
        scanf("%d",&arr1[i]);
    }

    printf("Enter array2: \n");
    for(int i=0;i<n;i++){
        scanf("%d",&arr2[i]);
    }

    #pragma omp parallel for
    for(int i=0;i<n;i++){
        arr3[i]=arr1[i]+arr2[i];
        printf(" arr[%d]=%d => Thread - %d\n",i,arr3[i], omp_get_thread_num());
    }
    
    free(arr1);
    free(arr2);
    free(arr3);


    return 0;
}