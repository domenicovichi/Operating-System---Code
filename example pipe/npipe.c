// example of named pipe

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

struct message_t
{
    int number;
    char text[64];
} msg;

int main(int argc, char *argv[])
{
    int fd, i = 0, n = 10;
    int size = sizeof(msg);
    srand(time(NULL));                   // seed for random function
    mknod("my_pipe", S_IFIFO | 0666, 0); // create FIFO file
    if (argc == 2)
        fd = open("my_pipe", O_WRONLY); // producer
    else
    {
        fd = open("my_pipe", O_RDONLY); // consumer
        strcpy(msg.text, "Happy birthday");
    }
    for (i = 0; i < n; i++)
        if (argc == 2)
        {
            msg.number = rand() % 100 + 1; // casual number
            printf("producer: %s %d \n", msg.text, msg.number);
            write(fd, &msg, size); // i write the msg in pipe
            sleep(1);
        }
        else
        {
            read(fd, &msg, size); // read the msg from pipe
            printf("consumer: %s, %d", msg.text, msg.number);
            sleep(1);
        }
}