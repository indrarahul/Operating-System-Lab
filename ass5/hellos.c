#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE
#include <unistd.h>

int main()
{
	system ("/bin/stty raw");
	
	char s[500],c;
	int i=0;
	
	while(1)
	{
		read(0,&c,1);
		if(c=='\x04')
			{	
				s[i++]='\0';
				break;
			}
		if(c=='\x0d')
			{	
				s[i++]='\n';
			}
		
		s[i++] = c;
	}

	system ("/bin/stty cooked");
	
	// write(1,"\n",1);
	write(1,s,strlen(s));
	// write(1,"\n",1);

	return 0;
}