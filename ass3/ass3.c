#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>


int main()

{
		FILE fd;
        fd = fopen("test.txt","w");
        write(fd,"hey",3);
        close(fd);
        return 0;
}