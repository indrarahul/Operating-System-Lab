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
#define MTX 0
#define WRT 1

union semun {
   int val;                         // value  for SETVAL
   struct semid_ds *buf;            // buffer for IPC_STAT, IPC_SET
   unsigned short int *array;       // array  for GETALL, SETALL
   struct seminfo *__buf;           // buffer for IPC_INFO
 }arg;

void init_sem(int semid,int semnum, int val)
{
  arg.val = val;
  semctl(semid,semnum,SETVAL,arg);
}

int main( ){

        char c;
        int             semid,shmid;
        key_t           key=1234,key_s=5678;
        
        if ((semid = semget(key, 2, IPC_CREAT | 0666)) == -1) {
         perror("semget: IPC_CREAT | 0660");
         return 1;
       }

       if ((shmid = shmget(key_s, sizeof(int), IPC_CREAT | 0666)) == -1) {
         perror("shmget: IPC_CREAT | 0666");
         return 1;
       }

       int *readcount = (int *)shmat(shmid,NULL,0);
       (*readcount)=0;

     init_sem(semid,MTX,1);
     init_sem(semid,WRT,1);

    
     return 0;
   }