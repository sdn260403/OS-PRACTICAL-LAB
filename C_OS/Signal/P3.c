#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>

void sigHand(int x)
{
        //printf("INTERRUPT HANDLING STARTED\n");
        int y;
        printf("ENTER A YEAR: ");
        scanf("%d",&y);
        if(y%4==0 && y%100!=0 || y%400==0)
                printf("Year %d is Leap Year\n",y);
        else
                printf("Year %d is not a Leap Year\n",y);
        //printf("INTERRUPT HANDLING ENDED\n");
}

int main()
{
        int pid=fork();
        if(pid==0)
        {
                //printf("\nCHILD PROCESS ENTERED\n");
                while(1)
                {
                        signal(SIGALRM,sigHand);
                }
        }
        else
        {
             while(1)
             {
                //printf("\nPARENT GOING INTO SLEEP MODE FOR 5 SEC\n");
                sleep(5);
                kill(pid,SIGALRM);
                
             }
        }
        return 0;
}
