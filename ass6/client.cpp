#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <unistd.h>
using namespace std;
int main()
{
	key_t key = ftok("shmfile",65);
	int shmid = shmget(key,sizeof(int),0666|IPC_CREAT);
	int *fact = (int *) shmat(shmid,(void *)0,0);

	for(int i=1;i<=20;i++)
				{
					*fact = i;
					cout << "Sending " << i <<endl;
					sleep(1);
				}
				cout << "Done!! Tata\n";
	shmdt(fact);
	return 0;
}