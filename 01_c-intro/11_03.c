#include <stdio.h>

int _add_i(int x, int y){
    printf("int : ");
    return x+y;
}
double _add_d(double x, double y){
    printf("double : ");
    return x+y;
}
#define addd(X,Y) _Generic((X)+(Y), int:_add_i, default:_add_d)((X), (Y))

int main(){
    printf("%d\n", addd(1,2));
    printf("%d\n", addd(1,2.3));
    printf("%d\n", addd(1.2,3));
    printf("%d\n", addd(1.2,3.4));
}