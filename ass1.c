#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE
#include <unistd.h>

int fact(int i)
{
	if(i==0 || i==1)
		return 1;
	else
		return i*fact(i-1);
}

int main(int argc,char **argv)
{

	int i=0;
	int num;
	pid_t pid;
			pid = fork();
			
	for(i=1;i<argc;i++)
		{
			
			if(pid==0)
			{
				if(i!=1)
				pid = fork();
				if(pid>0)
				{
				printf("I'm Father and I'm dying!\n");
				exit(0);
				}
				if(pid==0){
				num = atoi(argv[i]);
				printf("The factorial of %d = %d\n",num,fact(num));}
			}
		}

		

	return 0;
}