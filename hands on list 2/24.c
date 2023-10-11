//Hands on list 2 || Name:Sreeparna Das || Roll No.-MT2023006 || Submission Date:14/10/2023

//24. Write a program to create a message queue and print the key and message queue id.
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 10

struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

int main()
{
    key_t key=12345;
    int msgid;

    // ftok to generate unique key
   // key = ftok("progfile", 65);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.mesg_type = 1;

    printf("msgid will be %d\n", msgid);
    printf("msgqueue key will be %d\n", key);

}

