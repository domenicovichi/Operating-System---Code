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
    char client_queue_name[16]; //client queue name
    sprintf(client_queue_name, "mq_%d", getpid());
    struct mq_attr attr; //queue attribute 
    attr.mq_flags = 0; //blocking queue
    attr.mq_maxmsg = MAX_MESSAGES; //max number of queued messages (10)
    attr.mq_msgsize = sizeof(msg_send);
    attr.mq_curmsgs = 0;

    qd_client = mq_open(client_queue_name,O_CREAT|O_RDONLY,QUEUE_PERMISSION,&attr);
    //opens the server queue to send its pid
    qd_server = mq_open(SERVER_QUEUE_NAME,O_WRONLY);
    printf ("request a number <press ENTER>:");
    char in_buf[10];
    msg_send.pid = getpid();
    if(argc > 1){
        strcpy(msg_send.text,argv[1]); //nickname
    }
    else{
        strcpy(msg_send.text, "Domenico"); //default nickname
    }
    while(fgets(in_buf, 2, stdin)){
        //send message to server
        mq_send(qd_server, (const char*)&msg_send,sizeof(msg_send),0);
        //receive respons from server
        mq_receive(qd_client, (char*)&msg_rcv, sizeof(msg_rcv),NULL);
        //show message
        printf("Client: message from server: %s \n\n",msg_rcv.text);
        printf("request a number <press ENTER>:");
    }
    mq_close (qd_client);
    mq_unlink (client_queue_name); //delete queue
    printf ("Client: goodbye \n");
}