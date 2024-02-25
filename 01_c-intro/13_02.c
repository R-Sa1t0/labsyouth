#include <stdio.h>

typedef struct{
    char name[100];
    int price;
    double weight;
} FRUIT;

void input(FRUIT* f){
    printf("name price weight : ");
    scanf("%s%d%lf",f->name,&f->price,&f->weight);
}
void print(FRUIT* f){
    printf("%s, %d yen, %g kg.\n", f->name, f->price, f->weight);
}

int main(){
    FRUIT a;
    input(&a);
    print(&a);
}