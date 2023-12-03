//Reader Writer

#include "i.h"
#define RW 4
typedef struct shared
{
	int rc;
	sem_t mutex,db;
}temp;
void Reader(temp *s,int x)
{
        printf("Reader %d wants to read\n",x);
	sem_wait(&s->mutex);
	s->rc+=1;
	if(s->rc==1)
		sem_wait(&s->db);
	sem_post(&s->mutex);
	sleep(1);
	printf("Reader %d is Reading\n",x);
	sem_wait(&s->mutex);
	sleep(1);
	s->rc-=1;
	if(s->rc==0)
		sem_post(&s->db);
	sem_post(&s->mutex);
	printf("Reader %d Has Read\n",x);
}

void Writer(temp *s,int x)
{
        printf("Writer %d wants to write\n",x);
	sem_wait(&s->db);
	printf("Writer %d is Writing\n",x);
	sem_post(&s->db);
	printf("Writer %d has Written\n",x);
}
void Handler(temp *s,int x)
{
	while(1)
	{
		
		sleep(1);
		Reader(s,x);
		sleep(1);
		Writer(s,x);
	}
}

int main()
{
	int i;
	temp *s;
	
	//CREATING SHARED MEMORY
	int shmid=shmget(IPC_PRIVATE,sizeof(temp),0666);
	s=(temp*)shmat(shmid,NULL,0);

	//INITIALIZING SHARED MEMORY
	sem_init(&s->mutex,1,1);
	sem_init(&s->db,1,1);
	s->rc=0;

	//CREATING PROCESSES
	for(i=0;i<RW;i++)
	{
		int pid=fork();
		if(pid==0)
			Handler(s,i+1);
	}
	for(i=0;i<RW;i++)
		wait(NULL);

	shmdt(s);
	shmctl(shmid,IPC_RMID,NULL);
	
	return 0;

}

