//Hands on list 2 || Name:Sreeparna Das || Roll No.-MT2023006 || Submission Date:14/10/2023
//20) Write two programs so that both can communicate by FIFO -Use one way communication.


#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
int main(){
int res,n;
res=open("fifo1",O_WRONLY);
write(res,"murli sending the message", 26);
printf("sender pid is %d\n",getpid());
}

