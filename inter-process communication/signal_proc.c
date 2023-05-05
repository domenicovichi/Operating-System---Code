#include <signal.h>

void manager(int signum)
{
    static int count = 0;
    printf("Process with pid %d : received %d times the signal %d \n", getpid(), ++count, signum);
}

int main()
{
    __pid_t pid;
    signal(SIGUSR1, manager);
    pid = fork();
    if (pid == 0) /*son*/
        for (;;)
            pause();
    else /*father*/
        for (;;)
        {
            kill(pid, SIGUSR1); //send signal SIGUSR1 (10)
            sleep(1);
        }
}