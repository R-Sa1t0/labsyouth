#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char name[100];
    int price;
    double weight;
} FRUIT;

int main(){
    int count;
    printf("count: ");
    scanf("%d",&count);
    FRUIT* p=malloc(sizeof(FRUIT)*count);
    for (int i=0;i<count;i++){
        scanf("%s%d%lf", p[i].name, &p[i].price, &p[i].weight);        
    }
    for (int i=0; i<count; i++){
        printf("%p %s %d %g\n", p+i, p[i].name, p[i].price, p[i].weight);
    }
    free(p);
}