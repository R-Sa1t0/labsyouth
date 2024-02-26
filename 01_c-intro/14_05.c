#include <stdio.h>
#include <stdlib.h>

int main(){
    char* p=malloc(1);
    printf("%p 1\n", p);
    for (int i=2; i<100; i++){
        p=realloc(p,i);
        printf("%p %d\n",p ,i);
    }
    free(p);
}