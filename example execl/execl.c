/*Example showing the use of the "execl" function*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    __pid_t ret;
    int stato;
    ret = fork();
    printf("pid = %d \n", getpid());
    if (ret == 0)
    {
        // child
        execl("./new", "Hello", "From", "Father", (char *)0);
        printf("failed execl");
        exit(1);
    }
    else if (ret > 0)
    {
        printf("father with pid = %d \n", getpid());
        ret = wait(&stato);
    }
    else
    {
        printf("fork error");
    }
}