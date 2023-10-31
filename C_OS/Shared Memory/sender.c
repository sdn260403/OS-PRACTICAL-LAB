#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>

typedef struct shared
{
        char m[100];
        int res;
}s;

int main()
{
        s *shm;
        int shm_id=shmget((key_t)120,sizeof(s),0666|IPC_CREAT);//create the memory
        printf("Id of the Memory: %d\n",shm_id);
        shm=(s*)shmat(shm_id,NULL,0);//Attach the memory
        
        printf("ENTER DATA TO SHARED MEMORY: ");
        scanf("%[^\n]",shm->m);
        getchar();
        
        shm->res=2;
        while(shm->res==2);
        
        printf("Data Received is :%d\n",shm->res);
        if(shm->res==0) 
                printf("Hence NOT palindrome string\n");
	else 
	        printf("Hence palindrome string\n");
	        
	shmdt(shm);
	shmctl(shm_id,IPC_RMID,NULL);       
        
        return 0;
}
