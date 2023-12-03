//Producer Consumer

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#include "buffer.h"

sem_t mutex,full,empty;

void* producer(void* arg)
{
        int count=1;
        while(1)
        {
                
                sem_wait(&empty); 
                sem_wait(&mutex);
                printf("PRODUCER PRODUCES ITEM %d\n",count);  
                buf_insert(count);
                sleep(1);
                count++;                
                sem_post(&mutex);
                sleep(1);
                sem_post(&full); 
        }
}
void* consumer(void* arg)
{
        int count;
        while(1)
        {
               
                sem_wait(&full); 
                sem_wait(&mutex);
                count=buf_del();
                printf("CONSUMER CONSUMES ITEM %d\n",count);  
                sleep(1);               
                sem_post(&mutex);
                sleep(1);
                sem_post(&empty); 
        }
}
int main()
{
        int n;
        printf("ENTER LENGTH OF BUFFER: ");
        scanf("%d",&n);
        
        buffer_init(n);
        
        pthread_t p,c;
        sem_init(&mutex,0,1);
        sem_init(&full,0,0);
        sem_init(&empty,0,n);
        
        pthread_create(&p,NULL,&producer,NULL);
        pthread_create(&c,NULL,&consumer,NULL);
        
        pthread_join(p,NULL);
        pthread_join(c,NULL);
        
        return 0;
}
