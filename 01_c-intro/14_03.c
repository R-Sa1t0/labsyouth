#include <stdio.h>
#include <stdlib.h>

int main(){
    int* p0=malloc(sizeof(int));
    *p0=123;
    printf("%p\n", p0);
    printf("%d\n",*p0);
    free(p0);

    int count;
    printf("count: ");
    scanf("%d",&count);
    int* p=malloc(sizeof(int)*count);
    for (int i=0;i<count;i++) scanf("%d",p+i);
    for (int i=0;i<count;i++) printf("%p %d\n",p+i,p[i]);
    free(p);
}