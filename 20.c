// Question : Find out the priority of your running program. Modify the priority with nice command
//
#include <unistd.h>
#include <stdio.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<stdlib.h>

int main()
{
	int niceV;
	int pid=getpid();


	niceV= getpriority(PRIO_PROCESS,0);
	printf("pid : %d, nice : %d\n", pid,niceV);

	getchar();


	nice(5);// incrementing the proces's nice number by 5

	niceV=getpriority(PRIO_PROCESS,0);
	printf("pid :%d , nice : %d\n",pid,niceV);

	while(1);
	return 0;
}

