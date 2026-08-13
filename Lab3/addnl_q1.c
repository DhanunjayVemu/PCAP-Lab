#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define MAX_LINES 100
#define MAX_LEN 200

int main()
{
    char filename[100];
    char lines[MAX_LINES][MAX_LEN];
    int lineCount = 0;
    int threads;

    printf("Enter file name: ");
    scanf("%s", filename);

    printf("Enter number of threads: ");
    scanf("%d", &threads);

    FILE *fp = fopen(filename, "r");

    if(fp == NULL)
    {
        printf("Cannot open file.\n");
        return 1;
    }

    // Read all lines
    while(fgets(lines[lineCount], MAX_LEN, fp) != NULL)
    {
        lineCount++;
    }

    fclose(fp);

    omp_set_num_threads(threads);

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();

        for(int i = tid; i < lineCount; i += threads)
        {
            char temp[MAX_LEN];
            strcpy(temp, lines[i]);

            printf("\nThread %d processing Line %d:\n", tid, i + 1);
            printf("Original Line: %s", temp);

            printf("Tokens: ");

            char *token = strtok(temp, " \t\n");

            while(token != NULL)
            {
                printf("%s ", token);
                token = strtok(NULL, " \t\n");
            }

            printf("\n");
        }
    }

    return 0;
}