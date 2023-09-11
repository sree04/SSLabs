/*
    Question: Write a program to perform Record locking. 
    1. Implement write lock 
    Create three records in a file. Whenever you access a particular record, first lock it then modify/access to avoid race condition.
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>

struct file{
	int data;
};

int main(){
	int fd=open("record.txt",O_RDONLY|O_WRONLY);
	struct file v1,v2,v3;
	v1.data=1;
	v2.data=1;
	v3.data=1;
	write(fd,&v1,sizeof(v1));
	write(fd,&v2,sizeof(v2));
	write(fd,&v3,sizeof(v3));
	close(fd);
	return 0;
}

