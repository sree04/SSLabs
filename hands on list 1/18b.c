/*
    Question: Write a program to perform Record locking.
    2. Implement read lock
    Create three records in a file. Whenever you access a particular record, first lock it then modify/access to avoid race condition.
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>

struct record{
	int data;
};

int main(){
	int fd=open("record.txt",O_RDWR);
	int choice;
	printf("Enter record number to lock");
	scanf("%d",&choice);
	int offset = (choice-1)*sizeof(struct record);
	lseek(fd,offset,SEEK_SET);
	printf("Record locking in process.Kindly wait\n");
	struct flock lock;
	lock.l_type=F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=offset;
	lock.l_len=sizeof(struct record);
	lock.l_pid=getpid();
	fcntl(fd,F_SETLKW,&lock);
	printf("Locking...\n");
	struct record cur_rec;
	read(fd,&cur_rec,sizeof(cur_rec));
	printf("Previous record number was %d\n",cur_rec.data);
	printf("Press any key to unlock \n");
	getchar();
	getchar();
	cur_rec.data++;
	printf("your record number will be %d\n",cur_rec.data);
	lseek(fd,(-1)*sizeof(struct record),SEEK_CUR);
	write(fd,&cur_rec,sizeof(cur_rec));
	printf("You have your record\n");
	lock.l_type= F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	return 0;

}

 
   

