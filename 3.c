//. Write a program to create a file and print the file descriptor value. Use creat ( ) system  //call
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	int fd;
	fd=creat("new_file.txt",S_IRUSR |S_IWUSR);// user has read and write permission
	
	if(fd==-1)
	{
		perror("Error");//printing error msg
		exit(1);
	}

	printf("file descriptor value:%d\n",fd);

	close(fd);

	return 0;
}

