#include<stdio.h>
#include<unistd.h>
#include <sys/wait.h>
#include<string.h>
#define MS 100
int main()
{
        int fd[2],n;
        char buffer[100];
        pipe(fd);
        int pid=fork();
        if(pid>0)
        {
                printf("PARENT PROCESS: \n");
                read(fd[0],buffer,MS);
                printf("MESSAGE RECEIVED  IS: %s\n",buffer);
        }
        else
        {
                printf("CHILD PROCESS: \n");
                printf("ENTER MESSAGE TO BE PASSED: \n");
                scanf("%[^\n]s",buffer);
                write(fd[1],buffer,strlen(buffer));
        }
}
