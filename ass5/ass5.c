#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define _GNU_SOURCE
#include <unistd.h>

int main(int argc,char **argv)
{
	pid_t pid;	
	char buf[500],c;
	int pfd[2];
	pipe(pfd);
	
	pid = fork();

	if(pid==0)
	{
		
		close(pfd[0]); // Child closes Read end;
		dup2(pfd[1],1);
		char *arf[]={"./sca",NULL};
		execvp("./sca",arf);
		close(pfd[1]); // Child closes Write end after use;
		exit(0);
	
	}

	else
	{
		wait(NULL);
		close(pfd[1]);  // Parent closes Write end;
			
			dup2(pfd[0],0);
			
			int fd1 = open("file.txt",O_WRONLY | O_CREAT);
			int i=0;
			
			char *ard[]={"./wc","-l","file.txt",NULL};
			char *ard1[]={"./wc","-c","file.txt",NULL};
			char *ard2[]={"./wc","-w","file.txt",NULL};
			char *ard3[]={"./wc","file.txt",NULL};

			while(read(pfd[0],&c,1))
				{
					buf[i++] = c;
				}
				buf[i++]='\0';
			
			write(fd1,&buf,strlen(buf));
			
if(argc==3){
			if(strcmp(argv[1],"-l")==0)
				execvp("./wc",ard);
			if(strcmp(argv[1],"-c")==0)
				execvp("./wc",ard1);
			if(strcmp(argv[1],"-w")==0)
				execvp("./wc",ard2);
				}
				else if(argc==2)
				{
					if(strcmp(argv[1],"-l")==0)
					execvp("./wc",ard);
				}		

		close(pfd[1]); // Child closes Write end after use;
		exit(0);
	}

}