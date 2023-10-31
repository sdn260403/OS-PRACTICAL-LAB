#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
    
    int id= fork();
  
    if (id!=0)
    {
        printf("\nParent is created\n");
        sleep(5);
        printf("Parent is killed\n");
    }
    else
    {
        printf("Child is created\n");
        sleep(10);
        printf("Child is Orphan now\n");
    }
  
    return 0;
}
