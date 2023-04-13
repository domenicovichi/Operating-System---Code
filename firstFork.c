/*this program realizes the creation of a process*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    __pid_t ret;
    ret = fork();
    if (ret == -1)
    {
        printf("fork error");
        exit(0);
    }
    else if (ret == 0)
    {
        // child code
        printf("child with pid = %d \n", getpid());
    }
    else
    {
        // father code
        printf("father with pid = %d \n", getpid());
    }
    // this instruction is executed by both the father and the son
    printf("instruction executed by pid: %d \n", getpid());
}