//Dining_Philosopher


#include "i.h"
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define N 5

typedef struct shared_data
{
        int state[N];
        sem_t mutex;
        sem_t S[N];
}s;

void test(s *x,int id)
{
        int left=(id+N-1)%N,right=(id+1)%N;
        if(x->state[id]==HUNGRY && x->state[left]!=EATING && x->state[right]!=EATING)
        {
                x->state[id]=EATING;
                sleep(1);
                printf("Philosopher %d is Eating\n", id);
                sem_post(&x->S[id]);
        }
}
void take_fork(s *x,int i)
{
        sem_wait(&x->mutex);
        x->state[i]=HUNGRY;
        printf("Philosopher %d is Hungry\n", i);
        test(x,i);
        sem_post(&x->mutex);
        sem_wait(&x->S[i]);
        sleep(1);
}

void put_fork(s *x,int i)
{
        int left=i,right=(i+1)%N;
        sem_wait(&x->mutex);
        x->state[i]=THINKING;
        printf("Philosopher %d putting fork %d and %d down\n",i, left,right);
        printf("Philosopher %d is thinking\n", i);
        test(x,left);
        test(x,right);
        sem_post(&x->mutex);
}
void philosopher(s *x,int i)
{
        
        while(1)
        {
                sleep(1);
                take_fork(x,i);
                sleep(1);
                put_fork(x,i);
        }
}

int main()
{
        int i,p[N]={0,1,2,3,4};
        s *shm;
        
        //CREATING SHARED MEMORY
        int shmid=shmget(IPC_PRIVATE,sizeof(s),0666);
        shm=(s*)shmat(shmid,NULL,0);
        
        //INITIALIZING SHARED MEMORY DATA
        for(i=0;i<N;i++)
        {
                shm->state[i]=2;
                sem_init(&shm->S[i],1,0);
                printf("Philosopher %d is thinking\n",i);
        }
        sem_init(&shm->mutex,1,1);
        
        for(i=0;i<N;i++)
        {
                pid_t pid=fork();
                if(pid==0)
                        philosopher(shm,p[i]);
        }
        
        
        // Wait for all philosopher processes to finish
        for (int i = 0; i < N; i++) 
                wait(NULL);
    
        shmdt(shm);
        shmctl(shmid,IPC_RMID, NULL);
                
        return 0;
}
