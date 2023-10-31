#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void* compute(void* x)
{
	int s=0;
	int i,y;
	for(i=0;i<*(int*)x;i++)
	{
		printf("ENTER A NUMBER: ");
		scanf("%d",&y);
		s+=y;
	}
	pthread_exit((void*)s);	
}
int main()
{
	pthread_t t;
	int n;
	int *res;
	printf("ENTER THE TERMINAL VALUE: ");
	scanf("%d",&n);
	pthread_create(&t,NULL,&compute,&n);
	pthread_join(t,(void *)res);
	printf("THE RESULT IS : %d\n",*res);
	
	return 0;
}
