#include <stdio.h>
#include <sys/ipc.h> 
#include <sys/sem.h>
#include <sys/types.h> 
#include <stdlib.h>
#include <sys/shm.h> 
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#define _GNU_SOURCE
#include <unistd.h>
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
	
	int semid;
	key_t key=1234;
	int fd =open("test.txt",O_WRONLY | O_CREAT | O_APPEND);
	semid = semget(key,2,IPC_CREAT|0666);

	char msg[500],c;
	
		waitwa(semid,WRT);
		printf("Enter your message\n");
		gets(msg);
		write(fd,msg,strlen(msg));
		close(fd);
		printf("Done Writing\n");
		// gets(c);
		signalwa(semid,WRT);


}