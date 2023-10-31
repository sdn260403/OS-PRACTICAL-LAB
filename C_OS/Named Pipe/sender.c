#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAX 100

int main()
{
	int p;
	char *myfifo="./myfifo";
	char b1[100],b2[100],data[MAX];
	
	mkfifo(myfifo,0666);
	
	p=open(myfifo,O_WRONLY);
	
	printf("Enter the string 1 : ");
	scanf("%s",b1);
	write(p,b1,strlen(b1)+1);
	
	printf("Enter the string 2 : ");
	scanf("%s",b2);
	write(p,b2,strlen(b2)+1);
	
	close(p);
	
	p=open(myfifo,O_RDONLY);
	read(p,data,MAX);
	printf("Data sent by process 2\n");
	printf("%s and %s are %s \n",b1,b2,data);
	close(p);
}
