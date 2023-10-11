//Hands on list 2 || Name:Sreeparna Das || Roll No.-MT2023006 || Submission Date:14/10/2023

//21. Write two programs so that both can communicate by FIFO -Use two way communications.
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main()
{
        int fd;
        mkfifo("myFIFO",0666);

        char str1[80],str2[80];
        while(1)
        {
                fd = open("myFIFO",O_RDONLY);
		read(fd,str1,80);
		
		printf("User1: %s\n",str1);
		close(fd);

                fd = open("myFIFO",O_WRONLY);
		fgets(str2,80,stdin);
		write(fd,str2,strlen(str2)+1);
             	close(fd);
        }
        return 0;
}


