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

