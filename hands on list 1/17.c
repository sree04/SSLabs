// Question : Write a program to simulate online ticket reservations. Implement a write lock.  Write a program to open a file, store a ticket number, and exit.  Write a separate program, to open the file,  implement write lock, read the ticket number, increment the number, and print the new ticket number then close the file

#include<stdlib.h>
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
    int ticket;
    ticket=1;
   int fd=open("q171.txt",O_RDWR);
    if(fd==-1){
    return -1;
    }
    else{
    write(fd,&ticket,sizeof(ticket));
    }
    printf("Ticket no: %d\n",ticket);
    close(fd);
    return 0;
}

