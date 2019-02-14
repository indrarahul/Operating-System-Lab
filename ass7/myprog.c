#include <stdio.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

char *msg2;
static void print_msg()
{
	puts(msg2);
}

int main(int argc, char *argv[])
{

	sigset_t set,set2;
	int sig,sig2;
	int *sigptr = &sig,*sigptr2=&sig2;
	sigemptyset(&set);
	sigemptyset(&set2);
	sigaddset(&set,SIGUSR1);
	sigaddset(&set2,SIGUSR2);	
	sigprocmask( SIG_BLOCK, &set, NULL );
	sigprocmask( SIG_BLOCK, &set2, NULL );
	
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

	msg2 = msg;
	while(1){
	
	sigwait(&set,sigptr);
	if(*sigptr==10 || *sigptr==30 || *sigptr==16)
		print_msg();

			{
				printf("$ ") ;
				gets(msg);
				kill(pid, SIGUSR2);
			}
	}
	
	}
	
	else{
			
			while(1){
		
			printf("$ ") ;
			gets(msg);
			msg2 = msg;
			kill(pid, SIGUSR1);
			sigwait(&set2,sigptr2);
			if(*sigptr2==12 || *sigptr2==31 || *sigptr2==17)
			print_msg();

		}
	}

	shmdt(msg);
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}