#include <stdio.h>

int main(){
    int total = 0;
    for (int price;scanf("%d", &price), price; total+=price);
    printf("total : %d\n", total);
}