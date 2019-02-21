#include <stdio.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int m,n;
int border(int i,int j)
{
	 if(i < 0 || j < 0 ||  i > m-1 ||  j > n-1)
	 	return 0;
	 return 1;
}

void printarrb(int *b)
{
	int i,j;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{

			printf("%d ", b[i*n+j]);
		}

		printf("\n");
	}
}

void printarr(int a[m][n])
{
	int i,j;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{

			printf("%d ", a[i][j]);
		}

		printf("\n");
	}
}

void avg(int A[m][n],int *B,int i,int j)
{
	int k,avg,count=0,a[9];
	a[0] = ((border(i-1,j-1)==1) ? A[i-1][j-1]:0);
	a[1] = (border(i-1,j)==1) ? A[i-1][j]:0;
	a[2] = (border(i-1,j+1)==1) ? A[i-1][j+1]:0;
	a[3] = (border(i,j-1)==1) ? A[i][j-1]:0;
	a[4] = (border(i,j)==1) ? A[i][j]:0;
	a[5] = (border(i,j+1)==1) ? A[i][j+1]:0;
	a[6] = (border(i+1,j-1)==1) ? A[i+1][j-1]:0;
	a[7] = (border(i+1,j)==1) ? A[i+1][j]:0;
	a[8] = (border(i+1,j+1)==1) ? A[i+1][j+1]:0;
	for(k=0;k<9;k++)
		{if(a[k]!=0)
			count++;
			avg +=a[k];}
	
	avg /= count;
	B[i*n+j]=avg;

}

int main()
{

	int i,j;
	pid_t pid;
	printf("Enter m,n value\n");
	scanf("%d%d",&m,&n);
	int a[m][n];
	

	printf("Populate the Array A[m][n]\n");
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			scanf("%d",&a[i][j]);
	
	int shmid = shmget(IPC_PRIVATE,4*sizeof(int),IPC_CREAT|0666);
	int *b = (int *)shmat(shmid,NULL,0);
				


	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			pid = fork();
			if(pid==0)
			{
				avg(a,b,i,j);
				shmdt(b);
				exit(0);
			
}
			else
			{
				wait(NULL);
			}
		}
	}

		printf("\nB Array is as follows\n\n");
		printarrb(b);
		shmdt(b);
		shmctl(shmid,IPC_RMID,NULL);
	

return 0;
}