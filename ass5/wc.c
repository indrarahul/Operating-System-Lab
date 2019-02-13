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


	int fd;
	if(argc==3)
	fd = open(argv[2],O_RDONLY,O_CREAT);
	else
		fd = open(argv[1],O_RDONLY,O_CREAT);
	if(argc==1)
	{
		exit(0);
	}

	else{

				char msg[500],c;
				int i=0,w=0,co=0,l=1;
				
				while(read(fd,&c,1))
				{
					msg[i++] = c;
					if(c=='\n')
						l++;
					if(c==' ')
						w++;
				}
				
				co = strlen(msg);
				w += l;
				msg[i++]='\0';

				if(argc==2)
				{
					printf("\n%d %d %d\n", l,w,co);
				}

				if(argc == 3)

				{

					if(strcmp(argv[1],"-l")!=0 && strcmp(argv[1],"-c")!=0 && strcmp(argv[1],"-w")!=0 )
					{printf("wc: invalid option -- '%c'\n", argv[1][1]);
					exit(0);}
					else
					{	


						if(strcmp(argv[1],"-l")==0)
							printf("\nLines: %d\n", l);
						if(strcmp(argv[1],"-w")==0)
							printf("\nWords: %d\n", w);
						if(strcmp(argv[1],"-c")==0)
							printf("\nCount: %d\n", co);
					
					}
				}
	}
}