#define __LIBRARY__
#include <unistd.h>
#include<string.h>
#include<stdio.h>
_syscall2(int, whoami,char*,name,unsigned int,size);


int main()
{
	char out[24] = "";
	
	whoami(out,24);
	printf("%s\n",out);
	return 0;
}
