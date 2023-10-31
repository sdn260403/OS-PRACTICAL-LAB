#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>

typedef struct shared
{
        char m[100];
        int res;
}s;

int main()
{
        s *shm;
        int shm_id=shmget((key_t)120,sizeof(s),0666);//create the memory
        printf("Id of the Memory: %d\n",shm_id);
        shm=(s*)shmat(shm_id,NULL,0);//Attach the memory
        
        char st[100];
	int i,len,rt=1;
	
	strcpy(st,shm->m);
	
	len=strlen(st);
	for(i=0;i<strlen(st)/2;i++)
	{
		if(st[i]!=st[len-1-i])
		{
			rt=0;
			break;
		}
	}
	shm->res=rt;
	printf("Result is ready\n");
	shmdt(shm);
	return 0;
}
