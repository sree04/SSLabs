#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>

int main(int argc, char* argv[]){
	if(argc!=2){
		printf("there was a Error with the input file \n");
		return 1;
	}
	char *filename=argv[1];
	int fd=open(filename, O_RDONLY);
	if(fd==-1){
		printf("File Descriptor not working");
		return 1;
	}

	int flag=fcntl(fd, F_GETFL);
	if(flag==-1)
	{
		printf("Error \n");
		return 1;
	}


	if((flag & O_ACCMODE) == O_RDONLY){
		printf("the file %s was opened in Read Only Mode.\n", filename);
	}
 	else if((flag & O_ACCMODE) == O_WRONLY){
                printf("the file %s was opened in Write Only Mode.\n", filename);
        }
	else if((flag & O_ACCMODE) ==  O_RDWR){
                printf("the file %s was opened in Read Write Mode.\n", filename);
        }
	else{
                printf("the file %s was opened in an Unknown Mode.\n", filename);
        }

	close(fd);
	return 0;
}
