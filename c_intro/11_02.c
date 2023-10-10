#include <stdio.h>

inline int add(int x,int y){
    return x+y;
}

#define ADD(X,Y) ((X)+(Y))
// NG : #define ADD(X,Y) X+Y


int minus_i(int x){
    printf("int : ");
    return -x;
}
double minus_d(double x){
    printf("double : ");
    return -x;
}
#define minus(X) _Generic((X), int:minus_i, default:minus_d)((X))


int main(){
    //　コンパイルオプションで -O2 をつけて実行するとインライン化される
    // -O2がないとコンパイルが通らない！！！！！！！
    printf("%d\n", add(1,2));
    printf("%d\n", add(add(3,4),5));
    printf("%d\n", add(add(6,7),add(8,9)));
puts("");
    printf("%d\n", ADD(1<<2,3));
    printf("%d\n", ADD(1,2)*ADD(3,4));
puts("");
    printf("%d\n", minus_i(123));
    printf("%g\n", minus_d(1.23));
puts("");
    printf("%d\n", minus(123));
    printf("%g\n", minus(1.23));
}


