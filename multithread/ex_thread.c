/*The main thread creates two threads th1 and th2 and waits for their termination. The two threads concurrently execute the same code_T function.*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// shared variables
char MSG[] = "Hello";
void *codice_T(void *arg)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        printf("Thread %s: %s\n", (char *)arg, MSG);
        sleep(1);
    }
    pthread_exit(0);
}

int main()
{

    pthread_t th1, th2;
    int ret;
    /*first thread creation*/
    if (pthread_create(&th1, NULL, codice_T, "1") < 0)
    {
        fprintf(stderr, "Creation thread error 1 \n");
        exit(1);
    }
    /*second thread creation*/
    if (pthread_create(&th2, NULL, codice_T, "2") < 0)
    {
        fprintf(stderr, "Creation thread error 2 \n");
        exit(1);
    }

    ret = pthread_join(th1, NULL);
    if (ret != 0)
        fprintf(stderr, "failed join %d \n", ret);
    else
        printf("terminated thread 1 \n");
    ret = pthread_join(th2, NULL);
    if (ret != 0)
        fprintf(stderr, "failed join %d \n", ret);
    else
        printf("terminated thread 2");
    return 0;
}
