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
	fd = open("test.txt",O_RDONLY,O_CREAT);
	pd = fork();
	if(pd==0)
	{
		printf("From Child's Corner\n");
		while(child_buf[i]!='\0'){
		read(fd, child_buf,1);

		printf("\n%c\n", child_buf[i]);
		i++;}
	}

	else
	{
		close(fd);
	}
	return 0;
}