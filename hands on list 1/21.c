// Question : Write a program, call fork and print the parent and child process id.

#include <sys/types.h> // Import for `fork` & `getpid` system call
#include <unistd.h>    // Import for `fork` & `getpid` system call
#include <stdio.h>     // Import for printf function

void main()
{
    int childPid, pid;

    pid = getpid();// to get the pid of the calling process

    
   if (fork()!=0)
     printf("Parent PID: %d\n", pid);
     else 
	     childPid=getpid();
	     printf("Child pid = %d\n",childPid);

}

