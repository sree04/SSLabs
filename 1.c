//1. Create the following types of a files using (i) shell command (ii) system call
// a. soft link (symlink system call)
// b. hard link (link system call)
// c. FIFO (mkfifo Library Function or mknod system call)
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h> // to call symlink
int main(){

int v=symlink("dest","destSL");//softlink 
if(v<0)
{perror("Failed");return 1;}//if failed

int f=link("dest","desHL");//hardlink-call the link function to create a link to a file
			   
if(f<0)
{
	perror ("failed");
	return 1;
}

int e=mknod("deskFIFO",S_IFIFO,0);// make block or character special files 


if(e<0)
	perror("Failed");// print a system error message
	return 0;

	}

