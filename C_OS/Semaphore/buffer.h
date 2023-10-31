#include<stdio.h>
#include<stdlib.h>
struct
{
        int n;
        int* a;
        int f,r;
}b;

void buffer_init(int x)
{
        b.n=x;
        b.a=(int*)malloc(sizeof(int)*b.n);
        b.f=0;
        b.r=0;
}
void buf_insert(int x)
{
        b.a[b.r]=x;
        b.r=(b.r+1)%b.n;
}
int buf_del()
{
        int t=b.a[b.f];
        b.f=(b.f+1)%b.n;
        return t; 
}
