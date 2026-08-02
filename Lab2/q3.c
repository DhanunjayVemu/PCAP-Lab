/*3. Implement an OpenMP program to read a matrix of size M × N and produce:

• Matrix B, where all non-border elements are replaced by their 1's complement.
• Matrix D as specified. [Check the images in Lab 2 NE file]

Display both resulting matrices and indicate the Thread ID responsible for processing each row.*/

#include <stdio.h>
#include <omp.h>
#include <math.h>


int binary_to_decimal(int num)
{
    int ans = 0;
    int i = 0;

    while(num > 0)
    {
        int a = num % 10;

        ans = ans + pow(2, i) * a;

        num = num / 10;
        i++;
    }

    return ans;
}


int binary_complement(int num)
{
    int bin = 0;
    int arr[32];
    int i = 0;

    while(num > 0)
    {
        int a = num % 2;

        arr[i] = !a;

        num = num / 2;
        i++;
    }

    for(int j = i - 1; j >= 0; j--)
    {
        bin = bin * 10 + arr[j];
    }

    return bin;
}


int main()
{
    int m, n;

    printf("Enter matrix dimensions:\n");
    scanf("%d %d", &m, &n);

    int a[m][n], b[m][n], d[m][n];


    // Input matrix
    printf("Enter Matrix A:\n");

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }


    // Create Matrix B and D
    #pragma omp parallel for
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            // Border element
            if(i == 0 || j == 0 ||
               i == m-1 || j == n-1)
            {
                b[i][j] = a[i][j];
                d[i][j] = a[i][j];
            }

            // Non-border element
            else
            {
                b[i][j] =
                    binary_complement(a[i][j]);

                d[i][j] =
                    binary_to_decimal(b[i][j]);
            }
        }
    }


    // Matrix B
    printf("\nMatrix B:\n");

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%d\t", b[i][j]);
        }

        printf("\n");
    }


    // Matrix D
    printf("\nMatrix D:\n");

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%d\t", d[i][j]);
        }

        printf("\n");
    }

    return 0;
}