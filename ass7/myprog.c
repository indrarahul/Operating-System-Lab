#include <stdio.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>


static void print_msg(char *msg)
{
	puts(msg);
}

int main(int argc, char *argv[])
{

	sigset_t set;
	int sig;
	int *sigptr = &sig;
	sigemptyset(&set);
	sigaddset(&set,SIGUSR1);	
	sigprocmask( SIG_BLOCK, &set, NULL );
	
	int self,pid = atoi(argv[1]);
	key_t k = atoi(argv[2]);
	
	int shmid = shmget(k,sizeof(char),0666|IPC_CREAT);
	char *msg = (char *)shmat(shmid,(void *)0,0);
	memset(msg,0,sizeof(msg));
	
	self = getpid();
	printf("Self PID > %d\n",self);

	if(strcmp(argv[1],"0")==0){
	printf("Enter Partner's PID\n");
	scanf("%d",&pid);

	while(1){
	
	sigwait(&set,sigptr);
	if(*sigptr==10 || *sigptr==30 || *sigptr==16)
		print_msg(msg);

			{
				printf("$ ") ;
				gets(msg);
				kill(pid, SIGUSR1);
			}
	}
	
	}
	
	else{
			
			while(1){
			printf("$ ") ;
			gets(msg);
			kill(pid, SIGUSR1);
			sigwait(&set,sigptr);
			if(*sigptr==10 || *sigptr==30 || *sigptr==16)
			print_msg(msg);

		}
	}

	shmdt(msg);
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}