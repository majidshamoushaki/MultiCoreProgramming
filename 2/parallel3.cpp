#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

typedef struct
{
    int *A, *B, *C;
    int n, m;
} DataSet;

void fillDataSet(DataSet *dataSet);
void printDataSet(DataSet dataSet);
void closeDataSet(DataSet dataSet);
void add(DataSet dataSet);

int main(int argc, char *argv[])
{
    double start_time, total_time;
    DataSet dataSet;
    if (argc < 3)
    {
        printf("[-] Invalid No. of arguments.\n");
        printf("[-] Try -> <n> <m> \n");
        printf(">>> ");
        scanf("%d %d", &dataSet.n, &dataSet.m);
    }
    else
    {
        dataSet.n = atoi(argv[1]);
        dataSet.m = atoi(argv[2]);
    }
    fillDataSet(&dataSet);
    printf("start adding ...\n");
    start_time = omp_get_wtime();
    add(dataSet);
    total_time = omp_get_wtime() - start_time;
    printf("time: %f \n", total_time);
    //    printDataSet(dataSet);
    closeDataSet(dataSet);
    system("PAUSE");
    return EXIT_SUCCESS;
}

void fillDataSet(DataSet *dataSet)
{
    int i, j;

    dataSet->A = (int *)malloc(sizeof(int) * dataSet->n * dataSet->m);
    dataSet->B = (int *)malloc(sizeof(int) * dataSet->n * dataSet->m);
    dataSet->C = (int *)malloc(sizeof(int) * dataSet->n * dataSet->m);

    srand(time(NULL));

    for (i = 0; i < dataSet->n; i++)
    {
        for (j = 0; j < dataSet->m; j++)
        {
            dataSet->A[i * dataSet->m + j] = rand() % 100;
            dataSet->B[i * dataSet->m + j] = rand() % 100;
        }
    }
}

void printDataSet(DataSet dataSet)
{
    int i, j;

    printf("[-] Matrix A\n");
    for (i = 0; i < dataSet.n; i++)
    {
        for (j = 0; j < dataSet.m; j++)
        {
            printf("%-4d", dataSet.A[i * dataSet.m + j]);
        }
        putchar('\n');
    }

    printf("[-] Matrix B\n");
    for (i = 0; i < dataSet.n; i++)
    {
        for (j = 0; j < dataSet.m; j++)
        {
            printf("%-4d", dataSet.B[i * dataSet.m + j]);
        }
        putchar('\n');
    }

    printf("[-] Matrix C\n");
    for (i = 0; i < dataSet.n; i++)
    {
        for (j = 0; j < dataSet.m; j++)
        {
            printf("%-8d", dataSet.C[i * dataSet.m + j]);
        }
        putchar('\n');
    }
}

void closeDataSet(DataSet dataSet)
{
    free(dataSet.A);
    free(dataSet.B);
    free(dataSet.C);
}

void add(DataSet dataSet)
{
    omp_set_num_threads(16);
    omp_set_nested(1);
    {
#pragma omp parallel for schedule(static, 128)
        for (int i = 0; i < dataSet.n; i++)
        {
#pragma omp parallel for schedule(static, 128)
            for (int j = 0; j < dataSet.m; j++)
            {
                dataSet.C[i * dataSet.m + j] = dataSet.A[i * dataSet.m + j] + dataSet.B[i * dataSet.m + j];
            }
        }
    }
}