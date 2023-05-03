//example of use unnamed pipe 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DIM 256
#define READ 0
#define WRITE 1

int main()
{
    int n, fd[2];
    int pid;
    char message[DIM];

    if (pipe(fd) < 0)
    {
        printf("pipe error");
        exit(1);
    }
    if((pid=fork())<0){
        printf("pipe error");
        exit(1);
    } else if (pid > 0){
        //father
        close(fd[READ]); //close channel not in use
        write(fd[WRITE], "Hello son", DIM);
    } else {
        //son
        close(fd[WRITE]); //close channel not in use
        n = read(fd[READ], message, DIM);
        printf("%s \n", message);
    }

}