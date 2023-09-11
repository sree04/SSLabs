#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>

int main(void)
{	
	char fpath[]="9.txt";
	struct stat fileinfo;
	
	 if(stat(fpath, &fileinfo)==0) //file path name and address of the struct stat typed variable
	 {
	        printf("Inode is:%lu\n",fileinfo.st_ino);
	        printf("no. of hard links is:%lu\n",fileinfo.st_nlink);
	        printf("UID :%u\n",fileinfo.st_uid);
		 printf("GID :%u\n",fileinfo.st_gid);
		 printf("Size is :%ld\n",fileinfo.st_size);
	        printf("Block is :%ld\n",fileinfo.st_blocks);
		 printf("Block Size is :%ld\n",fileinfo.st_blksize);
		  printf("Time of last access :%ld\n",fileinfo.st_atime);
		printf("Time of last modification :%ld\n",fileinfo.st_mtime);
	       printf("Time of last change :%ld\n",fileinfo.st_ctime);
	}
    
       }
