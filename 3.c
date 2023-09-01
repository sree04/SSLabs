#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	int fd;
	fd=creat("example.txt",S_IRUSR |S_IWUSR);
	
	if(fd==-1)
	{
		perror("Error");
		exit(1);
	}

	printf("file descriptor value:%d\n",fd);

	close(fd);

	return 0;
}

