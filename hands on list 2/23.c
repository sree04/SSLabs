//Hands on list 2 || Name:Sreeparna Das || Roll No.-MT2023006 || Submission Date:14/10/2023

//23. Write a program to print the maximum number of files can be opened within a process and size of a pipe (circular buffer).
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<errno.h>

void main(){
int fifostatus;
long maxfile;
long sizeofpipe;

fifostatus=mkfifo("fifo2", S_IRWXU);

if(fifostatus==-1){
printf("error");
}

else{
maxfile=sysconf(_SC_OPEN_MAX);
if(maxfile==-1){printf("error");}
else{printf("maximum no of ile that can be opened %ld\n", maxfile);}

sizeofpipe=pathconf("fifo2", _PC_PIPE_BUF);
if(sizeofpipe==-1){printf("error");}
else{printf("maximum size of pipe %ld\n", sizeofpipe);}
}
}



