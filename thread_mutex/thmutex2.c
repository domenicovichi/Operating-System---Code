/*The thread main creates an matrix of integers of size NxM by assigning each element of the array a random value between 0 and 255. After creating the array, the main thread creates N child threads each of which is tasked with performing the sum of one row of the array. Each thread adds the sum it has calculated to a variable named sumMat, which at the end of program execution will contain the sum of all the elements of the matrix. The value of the sumMat variable is to be printed to the screen by the main thread.*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define N 20
#define M 1024

pthread_mutex_t mut; // shared mutex
int a[N][M];         // matrix
int sumMat = 0;

void *rowSum_th(void *arg)
{
    int i = (int)arg;
    int j;
    int rowSum = 0;
    for (j = 0; j < M; j++)
    {
        rowSum += a[i][j];
        pthread_mutex_lock(&mut); /*prologue critical section*/
        sumMat += rowSum;
        printf("thread: %d rowSum: %d, sum: %d", i, rowSum, sumMat);
        sleep(1);
        pthread_mutex_unlock(&mut); /*epilogue critical section*/
        pthread_exit(0);
    }
}

int main()
{
    int i, j;
    pthread_t th[N];
    pthread_mutex_init(&mut, NULL);
    srand(time(NULL));
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            a[i][j] = rand() % 256;
        }
        for (i = 0; i < N; i++)
        {
            if (pthread_create(&th[i], NULL, rowSum_th, (int *)i) != 0)
            {
                fprintf(stderr, "error create thread i \n");
                exit(1);
            }
        }
        for (i = 0; i < N; i++)
        {
            pthread_join(th[i], NULL);
        }
        printf("Sum = %d \n", sumMat);
    }
}