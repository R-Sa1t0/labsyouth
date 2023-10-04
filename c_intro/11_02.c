#include <stdio.h>

inline int add(int x,int y){
    return x+y;
}

#define ADD(X,Y) ((X)+(Y))
// NG : #define ADD(X,Y) X+Y

int main(){
    //　コンパイルオプションで -O2 をつけて実行するとインライン化される
    printf("%d\n", add(1,2));
    printf("%d\n", add(add(3,4),5));
    printf("%d\n", add(add(6,7),add(8,9)));

    puts("");

    printf("%d\n", ADD(1<<2,3));
    printf("%d\n", ADD(1,2)*ADD(3,4));
}


