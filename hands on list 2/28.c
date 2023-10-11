//28. Write a program to change the exiting message queue permission. (use msqid_ds structure)
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<unistd.h>

void main()
{

int qid;
struct msqid_ds msginfo;
int msgctlstatus;

qid=msgget((key_t)1124,IPC_CREAT|0777);
if(qid==-1){printf("error");}
msgctlstatus=msgctl(qid,IPC_STAT, &msginfo);

if(msgctlstatus==-1){printf("error");}
printf("access permission: %od\n", msginfo.msg_perm.mode);

printf("did you want to chnage the permission\n");
printf("press enter if yes\n");
printf("if no do nothing\n");
getchar();
msginfo.msg_perm.mode=0666;
msgctlstatus=msgctl(qid,IPC_SET, &msginfo);
printf("access permission %od\n", msginfo.msg_perm.mode);
if(msgctlstatus==-1){printf("error");}

}


