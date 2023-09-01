#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>

int main(void)
{
	struct stat s;
	stat("select.c" ,&s);
	printf("Select. c inode number:%d\n",s.st_ino);
	printf("select . c no of hard links:%ld\n",s.st_nlink);
	printf("select. c uid:%ld\n",s.st_uid);
	printf("select.  c gid:%ld\n",s.st_gid);
	printf("select. c no of blocks:%ld\n",s.st_blocks);
	printf("select .c block size:%ld\n",s.st_blksize);
}
