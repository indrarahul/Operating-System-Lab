#include <stdio.h>
#include <sys/ipc.h> 
#include <sys/sem.h>
#include <sys/types.h> 
#include <stdlib.h>
#include <signal.h>
#include <sys/shm.h> 
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#define _GNU_SOURCE
#include <unistd.h>
#define MTX 0
#define WRT 1

union semun {
int val;
struct semid_ds *buf;
ushort * array;
}arg;


void waitwa(int semid,int semnum)
{

	struct sembuf *opr = malloc(sizeof(struct sembuf));
	opr->sem_num = semnum;
	opr->sem_op = -1;
	opr->sem_flg = 0;
	semop (semid, opr, 1);

}

void signalwa(int semid,int semnum)
{
	struct sembuf *opr = malloc(sizeof(struct sembuf));
	opr->sem_num = semnum;
	opr->sem_op = 1;
	opr->sem_flg = 0;
	semop (semid, opr, 1);
}

int main()
{
	int semid,shmid,i=0;
	key_t key=1234,key_s=5678;
	shmid = shmget(key_s,sizeof(int),IPC_CREAT|0666);
	int *readcount = (int*)shmat(shmid,NULL,0);
	int fd =open("test.txt",O_RDONLY|O_CREAT);
	semid = semget(key,2,IPC_CREAT|0666);
	
	char buf[500],c[56];

		waitwa(semid,MTX);
		(*readcount)++;
		if((*readcount)==1)
			waitwa(semid,WRT);
		signalwa(semid,MTX);
		printf("Reading....\n");
		while(read(fd,&c,1))
				{
					buf[i++] = c;
				}
				buf[i++]='\0';
		puts(buf);
		
		printf("\nDone Reading!!\n");
		// scanf("%c",&c);
		gets(c);
		close(fd);
		waitwa(semid,MTX);
		printf("\nDone Reading!!\n");
		(*readcount)--;
		if((*readcount)==0)
			signalwa(semid,WRT);
		signalwa(semid,MTX);


	return 0;
}
