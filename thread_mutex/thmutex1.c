/*The initial main tread creates two threads named Th1 and Th2. The two threads share the integer variable A which is initially assigned the value 10. The thread Th1 increments the value of A by 1 and waits 1 second, while Th2 decrements the value of A by 1 and waits 1 second. Both threads perform the above operations 10 times, then terminate.*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int A = 10;        // shared variable
pthread_mutex_t M; // mutual exclusion mutex

void *codeTh1(void *arg)
{
    int i = 0;
    for (i; i < 10; i++)
    {
        printf("Thread: %s ", (char *)arg);
        pthread_mutex_lock(&M); // prologue critical section
        A++;
        printf("A = %d \n", A);
        pthread_mutex_unlock(&M); // epilogue critical section
        sleep(1);
    }
    pthread_exit(0);
}

void *codeTh2(void *arg)
{
    int i = 0;
    for (i; i < 10; i++)
    {
        printf("Thread: %s ", (char *)arg);
        pthread_mutex_unlock(&M); // prologue critical section
        A--;
        printf("A = %d \n", A);
        pthread_mutex_unlock(&M); // epilogue critical section
        sleep(1);
    }
    pthread_exit(0);
}

int main()
{
    pthread_t th1, th2;
    if (pthread_create(&th1, NULL, codeTh1, "th1") != 0)
    {
        printf("creation thread 1 error");
    }
    if (pthread_create(&th2, NULL, codeTh2, "th2") != 0)
    {
        printf("creation thread 2 error");
    }

    if (pthread_join(th1, NULL) != 0)
    {
        printf("join 1 failed");
    }
    else
    {
        printf("1 thread terminated \n");
    }

    if (pthread_join(th2, NULL) != 0)
    {
        printf("join 2 failed");
    }
    else
    {
        printf("2 thread terminated \n");
    }
}