//Hands on list 2 || Name:Sreeparna Das || Roll No.-MT2023006 || Submission Date:14/10/2023
//19. Create a FIFO file by
// a. mknod command


#include <sys/stat.h>
#include <stdio.h>
int main(){
    int fd=mknod("myfifo",S_IFIFO|0666,0);
    if(fd==-1){
        printf("error\n");
        return -1;
    }
    printf("success\n");
    return 0;
}
