
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
