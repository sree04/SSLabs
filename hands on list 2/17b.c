//17. Write a program to execute ls -l | wc.
// b. use dup2

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
int main(){
    int lstowc[2];
    if(pipe(lstowc)==-1){
        printf("error\n");
        return -1;
    }
    pid_t frk=fork();
    if(!frk){
        //child
        //close read of the pipe
        //close(1);
        close(lstowc[0]);
        dup2(lstowc[1],1);
        execlp("ls","ls","-l",(char*)NULL);
        close(lstowc[1]);
    }else{
        //parent
        //close read end of pipe
        //close(0);
        close(lstowc[1]);
        dup2(lstowc[0],0);
        execlp("wc","wc",(char*)NULL);
        close(lstowc[0]);
    }
}
