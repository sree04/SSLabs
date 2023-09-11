// Question : Write a program to create a Zombie state of the running program

#include <sys/types.h> // Import for `fork` system call
#include <unistd.h>    // Import for `fork` system call
#include <stdio.h>     // Import for `printf` function

void main()
{
    pid_t childPid;

    if ((childPid = fork()) != 0)
    {
      
        printf("Parent PID: %d\n", getpid());
        printf("Putting parent to sleep for 100s!\n");
        sleep(60); // Put the calling  process to sleep for 60s
        printf("calling process  is now awake!\n");
    }
    else
    {
        // Only child process can enter this branch
        printf("Child PID: %d\n", getpid());
        printf("Exiting child!\n");
        _exit(0); //immediate  terminate the child process
       // we called fork cmd to create a child process,since parent and child both run simultaneously 
       //    we set the parent to sleep and child to exit immediately when parent process is sleeping.the child process sends the exit code which the parent is unable to check and zombie process is created.
       //
       }
}
