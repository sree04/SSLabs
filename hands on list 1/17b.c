#include<stdlib.h>
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
int ticket;
int fd=open("q171.txt",O_RDWR);
struct flock lock;
lock.l_type=F_WRLCK;
lock.l_whence=SEEK_SET;
lock.l_start=0;
lock.l_len=0;
lock.l_pid=getpid();
printf("Ticket reservation in process\n");
fcntl(fd,F_SETLKW,&lock);
read(fd,&ticket,sizeof(ticket));
printf("your previous seat number is:%d\n",ticket);
ticket++;
lseek(fd,0,SEEK_SET);
printf("Your seat number will be: %d\n",ticket);
write(fd, &ticket, sizeof(ticket));
printf("Press any key to confirm your seat\n");
getchar();
printf("Ticket Booked!");
lock.l_type=F_UNLCK;
fcntl(fd,F_SETLK,&lock);
}

