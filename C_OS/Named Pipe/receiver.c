#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#define MAX 100

int main()
{
	int p;
	char *ans="Not Same";
	
	char *myfifo="./myfifo";
	
	char b1[100],b2[100];
	
	p=open(myfifo,O_RDONLY);
	read(p,b1,MAX);
	read(p,b2,MAX);
	printf("Data sent by process 1\n");
	printf("%s and %s \n",b1,b2);
	close(p);
	
	
	p=open(myfifo,O_WRONLY);
	if(!strcmp(b1,b2))
		ans="Same";
	write(p,ans,strlen(ans));
	close(p);
}
