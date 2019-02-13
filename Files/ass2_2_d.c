#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>


int main(int argc,char **argv)
{

	int fd;
	pid_t pd;
	int i=0,x = 500;
	char child_buf[x],par_buf[x];
	fd = open("test.txt",O_WRONLY | O_CREAT);
	pd = fork();
	
	if(pd==0)
	{
		
		// CREATING BUFFER	
		memcpy(child_buf,"I am Child",15);
		
		//WRITING TO FILE
		write(fd,child_buf,strlen(child_buf));

	}

	else
	{
	
		
	}
	return 0;
}