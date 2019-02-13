#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <unistd.h>
using namespace std;

long long int facto(int n)
{
	if(n==0 || n==1)
		return 1;
	return (n)*facto(n-1);
}

int main()
{
	key_t key = ftok("shmfile",65);
	int shmid = shmget(key,sizeof(int),0666|IPC_CREAT);
	int *fact = (int *) shmat(shmid,(void *)0,0);
	int num;

	while((*fact)==0){
		cout << "Not Getting any number\n";
		sleep(1);
	}

	for(int i=0;i<20;i++){
		num = *fact;
		cout << "The Factorial of " << (*fact) << " is : " << facto(num)<<endl;
		sleep(1);
	}
	cout << "Done!! Tata\n";
	shmdt(fact);
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}