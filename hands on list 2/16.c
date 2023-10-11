//Hands on list 2 || Name:Sreeparna Das || Roll No.-MT2023006 || Submission Date:14/10/2023

//16. Write a program to send and receive data from parent to child vice versa. Use two way communication.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(){
    int pipeChildtoParent[2];
    int pipeParenttoChild[2];
    if(pipe(pipeChildtoParent)==-1 || pipe(pipeParenttoChild)==-1){
        printf("error");
        return -1;
    }
    pid_t frk=fork();
    if(!frk){
        //child
        //close read end of pipe
        close(pipeChildtoParent[0]);
        close(pipeParenttoChild[1]);
        char buff1[]="whatever I write here will be reflected when parent is running";
        char buff2[1000];
        write(pipeChildtoParent[1],buff1,sizeof(buff1));
        read(pipeParenttoChild[0],buff2,sizeof(buff2));
        printf("read from parent:\n");
        printf("%s",buff2);
        printf("\n");
        close(pipeChildtoParent[1]);
        close(pipeParenttoChild[0]);
    }else{
        //close read end of pipe
        close(pipeChildtoParent[1]);
        close(pipeParenttoChild[0]);
        char buff1[]="whatever I write here will be reflected when child is running";
        char buff2[1000];
        write(pipeParenttoChild[1],buff1,sizeof(buff1));
        read(pipeChildtoParent[0],buff2,sizeof(buff2));
        sleep(2);
        printf("read from child:\n");
        printf("%s",buff2);
        printf("\n");
        close(pipeChildtoParent[0]);
        close(pipeParenttoChild[1]);
    }
}
