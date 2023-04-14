#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i;
    printf("Process called by execl with PID = %d and PPID = %d \n", getpid(), getppid());
    for (i = 0; i < argc; i++)
    {
        printf("%s", argv[i]); // show input parameters
        printf("\n");
    }
}