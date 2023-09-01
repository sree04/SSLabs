#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc,char *argv[]){

	char *filename;
	int fileDes;

	if(argc !=2)
		write(STDOUT_FILENO,"PASS THE FILE TO BE OPENED AS ARGUMENT\n",33);
	else

	{
		filename=argv[1];

		fileDes=open(filename,O_RDWR);

		if(fileDes == -1)
			perror("enter while opening the file");
		else
			printf("the file was successfully created with the file desp->%d",fileDes);

	}

	
}

