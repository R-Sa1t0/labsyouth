#include <stdio.h>

int main(){
    int total = 0;
    for (;;){
        int price=0;
        scanf("%d", &price);
        if (price==0) break;
        if (price<0){
            puts("error : price<0");
            continue;
        }
        total +=price;
    }
    printf("total : %d\n", total);
}