#define __LIBRARY__

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h>           
#include <sys/stat.h>    
#include <errno.h>
#include<sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MUTEXNAME 	"mutex"
#define EMPTYNAME	"empty"
#define FULLNAME 	"full"
#define M	 	700
#define BUFFILENAME	"buffer.txt"
#define CONNUMFILE	"output.txt"

_syscall2(struct sem_t*, sem_open, const char *, name, unsigned int, value)
_syscall1(int, sem_wait, struct sem_t *, sem)
_syscall1(int, sem_post, struct sem_t *, sem)
_syscall1(int, sem_unlink, const char *, name)


struct sem_t* mutex = NULL;
struct sem_t* empty = NULL;
struct sem_t* full = NULL;


int producedItemNum = 0;

void Producer();
void Consumer();

void outputConsumedNum(char* cn);

int main()
{
	pid_t p1,p2,p3,p4,p5;
        int k=0;
	sem_unlink(MUTEXNAME);
	sem_unlink(EMPTYNAME);
	sem_unlink(FULLNAME);	
	mutex = sem_open(MUTEXNAME, 1);
	empty = sem_open(EMPTYNAME, 10);
	full = sem_open(FULLNAME, 0);

	p1 = fork();
	if (p1 == 0)
	{
		Producer();	
		return 1;
	}

	p2 = fork();
	if (p2 == 0)
	{
		Consumer();
		return 2;
	}
	p3 = fork();
	if (p3 == 0)
	{
		Consumer();
		return 3;
	}
	p4 = fork();
	if (p4 == 0)
	{
		Consumer();
		return 4;
	}
	p5 = fork();
	if (p5 == 0)
	{
		Consumer();
		return 5;
	}

	while(k < 10000000)
	{
	    ++k;
	}

	kill(p2, SIGKILL);
	kill(p3, SIGKILL);
	kill(p4, SIGKILL);
	kill(p5, SIGKILL);	
	
	sem_unlink(MUTEXNAME);
	sem_unlink(EMPTYNAME);
	sem_unlink(FULLNAME);	
	return 0;
}


void Producer()
{
	int fd;
	char numBuf[5];
	while(producedItemNum <= M)
	{
		sem_wait(empty);
		sem_wait(mutex);
		fd = open(BUFFILENAME,O_WRONLY|O_APPEND|O_CREAT, 0644);
		
		sprintf(numBuf, "%d", producedItemNum);
                ++producedItemNum;
		write(fd, numBuf, strlen(numBuf));
		write(fd, "\n", 1);
		close(fd);
		sem_post(mutex);
		sem_post(full);		
	}	

}

void Consumer()
{
	char numBuf[5];
	char readBuf;
	char fileBuf[100];
	int fd;
	int i,readCharNum;
	char printBuf[20];
	while(1)
	{
		i = 0;
		sem_wait(full);
		sem_wait(mutex);
		fd = open(BUFFILENAME, O_RDWR|O_CREAT, 0644);
		lseek(fd, 0, SEEK_SET);
		read(fd, &readBuf, 1);
		while(readBuf != '\n')
		{
			numBuf[i] = readBuf;
			++i;
			read(fd, &readBuf, 1);
		}
		numBuf[i] = '\0';
		++i;
		printf("%d: %s  ", getpid(), numBuf);
                sprintf(printBuf, "%d: %s\n", getpid(), numBuf);
		fflush(stdout);	

		outputConsumedNum(printBuf);
		lseek(fd, i, SEEK_SET);
		readCharNum = read(fd, fileBuf, 80);
		close(fd);
		
		fd = open(BUFFILENAME, O_RDWR|O_TRUNC);
		lseek(fd, 0, SEEK_SET);
		write(fd, fileBuf, readCharNum);
		close(fd);
		sem_post(mutex);
		sem_post(empty);
	}
}

void outputConsumedNum(char *cn)
{
	int fd = open(CONNUMFILE, O_CREAT|O_APPEND);
	write(fd, cn, strlen(cn));
	write(fd, "\n", 1);
	close(fd);
}
