//18. Write a program to find out total number of directories on the pwd.
// execute ls -l | grep ^d | wc ? Use only dup2.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
int main(){
    int lstogrepd[2];
    int greptowc[2];
    if(pipe(lstogrepd)==-1 || pipe(greptowc)==-1){
        printf("error\n");
        return -1;
    }
    pid_t frk=fork();
    if(!frk){
        //child
        close(greptowc[0]);
        close(greptowc[1]);
        close(lstogrepd[0]);
        dup2(lstogrepd[1],1);
        execlp("ls","ls","-l",(char*)NULL);
        close(lstogrepd[1]);
    }else{
        //parent
        if(!fork()){
            //child
            close(lstogrepd[1]);
            close(greptowc[0]);
            dup2(lstogrepd[0],0);
            dup2(greptowc[1],1);
            execlp("grep","grep","^d",(char*)NULL);
            close(lstogrepd[0]);
        }else{
            //parent
            close(lstogrepd[0]);
            close(lstogrepd[1]);
            close(greptowc[1]);
            dup2(greptowc[0],0);
            execlp("wc","wc",(char*)NULL);
        }
    }
}
