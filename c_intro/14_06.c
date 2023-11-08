#include <stdio.h>
#include <stdlib.h>

int main(){
    int count=0, capacity= 2;
    int* p=malloc(sizeof(int)*capacity);
    printf("%p %d/%d\n",p,count,capacity);
    for (int x; scanf("%d", &x), x;){
        if (count>=capacity){
            capacity+=2;
            p=realloc(p, sizeof(int)*capacity);
        }
        p[count++]=x;
        printf("%p %d/%d\n",p,count,capacity);
    }
    puts("");
    for (int i=0; i<count; i++) printf("%p %d\n", p+i, p[i]);
}