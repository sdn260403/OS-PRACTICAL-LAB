#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
    
    int id= fork();
  
    if (id!=0)
    {
        printf("\nParent is created\n");
        sleep(15);
    }
    else
    {
        printf("Child is created\n");
        sleep(5);
        printf("Child is Dead\n");
        exit(0);
    }
  
    return 0;
}
