//19. Create a FIFO file by
// b. mkfifo command

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
int main(){
    int fd=mkfifo("myfifo2",S_IFIFO|0666);
    if(fd==-1){
        printf("error\n");
        return -1;
    }
    printf("success\n");
    return 0;
}
