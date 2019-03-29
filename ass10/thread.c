#include <stdio.h>
#include <sys/ipc.h> 
#include <sys/sem.h>
#include <sys/types.h> 
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/shm.h> 
#include <sys/stat.h>
#include <fcntl.h>
#define _GNU_SOURCE
#include <unistd.h>
#include <pthread.h> 

pthread_mutex_t mtx;
int buf;

int k()
{
	int c1=0;
	pid_t pid = getpid();
	int tid;
	tid = pthread_self();

	while(1){
	pthread_mutex_lock(&mtx);
	printf(" Process ID: %d\n", (int)pid);
	printf(" Thread ID: %d\n", tid);
	printf(" BUFFER :%d\n", (buf));
	if(buf>=24)
	{
		pthread_mutex_unlock(&mtx);
		break;	
	}
	(buf)++;
	c1++;
	pthread_mutex_unlock(&mtx);
	sleep(1);
}
	return (void *)c1;
}

int main()
{
	pthread_t a,b,c;
	int *ctr;
	pthread_mutex_init(&mtx,NULL);
	
	pthread_create(&a,NULL,k,NULL);
	pthread_create(&b,NULL,k,NULL);
	pthread_create(&c,NULL,k,NULL);

	pthread_join(a,&ctr);
	printf("THREAD 1 got %d chance\n", (int)ctr);
	pthread_join(b,&ctr);
	printf("THREAD 2 got %d chance\n", (int)ctr);
	pthread_join(c,&ctr);
	printf("THREAD 3 got %d chance\n", (int)ctr);
	return 0;


}