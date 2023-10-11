//31. Write a program to create a semaphore and initialize value to the semaphore.
// b. create a counting semaphore


#include<pthread.h>
#include<stdio.h>
#include<semaphore.h>
#include<unistd.h>

void *fun1();
void *fun2();
int shared=1;
sem_t s;

int main()
{
sem_init(&s,0,2);

pthread_t thread1,thread2;
pthread_create(&thread1,NULL,fun1, NULL);
pthread_create(&thread2,NULL, fun2, NULL);
pthread_join(thread1,NULL);
pthread_join(thread2,NULL);
printf("final value of shared %d\n",shared);
}


void *fun1(){
int x;
sem_wait(&s);
//critical section start
x=shared;
printf("thraed read the value %d\n",x);
x++;
printf("local updation by thread1 %d\n",x);
sleep(1);
shared=x;
printf("value of shared variable updated by thread1 %d\n", shared);
//critical section end
sem_post(&s);
}



void *fun2(){
int y;
sem_wait(&s);
//critical section start
y=shared;
printf("thread2 read the value as %d\n",y);
y--;
printf("local updation by thraed2 %d\n",y);
sleep(1);
shared=y;
printf("value of shared variable by thraed2 %d\n",shared);
//critical section ends
sem_post(&s);
}

