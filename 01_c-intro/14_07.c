#include <stdio.h>
#include <stdlib.h>

char* input(){
    int count=0, capacity=1;
    char* p=malloc(capacity);
    for (int c; (c=getchar())!='\n';){
        if (count+1>=capacity){
            capacity*=2;
            p=realloc(p, capacity);
        }
        p[count++]=c;
        printf("%p %2d/%2d %c\n", p, count+1, capacity, c);
    }
    p[count]='\0';
    return p;
}
int main(){
    char *p=input();
    puts(p);
    free(p);
}