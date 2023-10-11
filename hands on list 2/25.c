//Hands on list 2 || Name:Sreeparna Das || Roll No.-MT2023006 || Submission Date:14/10/2023

//25. Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
// a. access permission
// b. uid, gid
// c. time of last message sent and received 
 //d. time of last change in the message queue
// e. size of the queue
// f. number of messages in the queue 
// g. maximum number of bytes allowed 
// h. pid of the msgsnd and msgrcv

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>

void main(){
int qid;
struct msqid_ds msginfo;
int msgctlstatus;

qid=msgget((key_t)1124,IPC_CREAT|0700);
if(qid==-1){printf("error");}

msgctlstatus=msgctl(qid,IPC_STAT, &msginfo);
if(msgctlstatus==-1){printf("error");}

printf("Access Permission: %od\n", msginfo.msg_perm.mode);
    printf("UID: %d\n", msginfo.msg_perm.uid);
    printf("GID: %d\n", msginfo.msg_perm.gid);
    printf("Time of last message sent: %ld\n", msginfo.msg_stime);
    printf("Time of last message received: %ld\n", msginfo.msg_rtime);
    printf("Size of queue: %ld\n", msginfo.__msg_cbytes);
    printf("Number of messages in the queue: %ld\n", msginfo.msg_qnum);
    printf("Maximum number of bytes allowed in the queue: %ld\n", msginfo.msg_qbytes);
    printf("PID of last sent message: %d\n", msginfo.msg_lspid);
    printf("PID of last received message: %d\n", msginfo.msg_lrpid);


}

