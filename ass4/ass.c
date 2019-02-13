#include <stdio.h> 
#include <sys/types.h>   
#include <stdlib.h> 
#include <errno.h>   
#include <sys/wait.h>
#define _GNU_SOURCE
#include <unistd.h>

int main(int argc,char **argv)
{
    int i=0;
	pid_t pid;
	for(i=1;i<argc;i++)
		{
            if((pid = fork())==0)
                execvp(argv[i],&argv[i]);   
		}
    return 0;
}