#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>


void handle(int);
int main()
{
        signal(SIGINT,handle);
        while(1)
        {
                printf("Hello!\n");
                sleep(2);
        }
        
        return 0;
}
void handle(int signum)
{
        printf("\nSignal No.: %d\n",signum);
        exit(0);
}

