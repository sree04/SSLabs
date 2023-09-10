/*
Question: Write a program to perform mandatory locking. 
    - Implement write lock 
*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
int main(){
struct flock lock;
int fd;
fd=open("out.txt",O_RDWR);
lock.l_type=F_WRLCK;
lock.l_whence=SEEK_SET;
lock.l_start=0;
lock.l_len=0;
lock.l_pid=getpid();
printf("before entering to critical section...\n");
fcntl(fd,F_SETLKW,&lock);
printf("inside the critical section...\n");
printf("enter to unlock");
getchar();
printf("unlocked\n");
lock.l_type=F_UNLCK;
fcntl(fd,F_SETLK,&lock);
printf("FINISH\n");
}

}


