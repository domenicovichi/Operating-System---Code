/*example of the use of Posix message queues, we realize a simple application with client/server architecture with the following specifications: 
- A set of client processes requests a unique serial number of integer type from a server process 
- The server responds to a client's request by sending a different number for each request
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <mqueue.h>

#define SERVER_QUEUE_NAME "/mq_server"
#define QUEUE_PERMISSION 0660
#define MAX_MESSAGES 10

struct message{
    int pid;
    char text[64];
} msg_send, msg_rcv;

int main(int argc, char const *argv[])
{
    mqd_t qd_server, qd_client; //queue descriptor
    long serial_number = 1;  //serial number to send to the client
    char client_queue_name[16]; //client queue name
    struct mq_attr attr; //queue attribute 
    attr.mq_flags = 0; //blocking queue
    attr.mq_maxmsg = MAX_MESSAGES; //max number of queued messages (10)
    attr.mq_msgsize = sizeof(msg_rcv);
    attr.mq_curmsgs = 0;

    printf ("Server: Welcome! \n");
    qd_server = mq_open(SERVER_QUEUE_NAME,O_RDONLY|O_CREAT, QUEUE_PERMISSION, &attr);

    while (1)
    {
        //Pulls the oldest message with highest priority from the queue
        mq_receive(qd_server,(char*)&msg_rcv,sizeof(msg_rcv),NULL);
        printf("Server: message received from client %d, %s \n", msg_rcv.pid, msg_rcv.text);
        sprintf(client_queue_name, "mq_%d", msg_rcv.pid);
        //sends the response message to the client
        qd_client = mq_open (client_queue_name, O_WRONLY);
        sprintf(msg_send.text, "Welcome client %d, your number is %ld", msg_rcv.pid, serial_number);
        mq_send (qd_client, (const char*)&msg_send,sizeof(msg_send),0);
        printf("Server: sends the response message to the client \n");
        serial_number ++;
    }
    
}

