#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>

void sigHand(int x)
{
        printf("\nSignal No.: %d.....Parent Stopped\n",x);
        exit(0);
}

int main()
{
        int pid=fork();
        if(pid==0)
        {
                printf("Child is running\n");
                sleep(2);
                printf("Child is killed....Sending Alarm to parent...");
                kill(getppid(),SIGALRM);
                
        }
        else
        {
                signal(SIGALRM,sigHand);
                while(1)
                {
                        printf("\nHELLO!I am the parent.");
                        sleep(1);
                }
        }
        return 0;
}
