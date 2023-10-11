//Hands on list 2 || Name:Sreeparna Das || Roll No.-MT2023006 || Submission Date:14/10/2023

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
int main()
{
int res,n;
char buffer[100];
res=open("fifo1", O_RDONLY);
n=read(res,buffer,100);
printf("reader process pid %d\n", getpid());
printf("data is received is %s\n", buffer);

}

