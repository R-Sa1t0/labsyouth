#include <stdio.h>

int add(int x, int y){
    return x+y;
}
int main(){
    int (*p)(int,int)=add;
    printf("%d\n", p(1,2));
}