#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char name[100];
    int price;
    double weight;
} FRUIT;

int main(){
    FRUIT* fruit=malloc(sizeof(FRUIT));
    int n=0, capacity=1;
    FILE* fp=fopen("15_10.out", "r");

    while (fscanf(fp, "%s%d%lf", fruit[n].name, &fruit[n].price, &fruit[n].weight)!=EOF){
        if (++n>=capacity){
            capacity*=2;
            fruit=realloc(fruit, sizeof(FRUIT)*capacity);
        }
    }

    fclose(fp);

    for (int i=0; i<n; i++){
        printf("%-6s %5d %6.1f\n", fruit[i].name, fruit[i].price, fruit[i].weight);
    }
}