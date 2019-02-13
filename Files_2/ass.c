#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>


int main()

{

        FILE *fd = fopen("test.txt","w");
        fprintf(fd,"%s", "hey");
        fclose(fd);
        return 0;
}