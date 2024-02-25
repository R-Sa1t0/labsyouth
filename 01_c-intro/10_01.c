#include <stdio.h>

int add(int x, int y);

int main(){
    printf("%d\n", add(1,2));
    printf("%d\n", add(add(3,4),5));
    printf("%d\n", add(add(6,7),add(8,9)));
}

int add (int x, int y){
    return x+y;
}