#include <stdio.h>

typedef struct
{
    char name[100];
    int price;
    double weight;
} FRUIT;

int main(){
    FRUIT fruit[]={
        {"Apple", 150, 0.4},
        {"banana", 20, 0.2},
        {"kiwi", 130, 0.1},
        {"melon", 900, 2.0},
        {"orange", 100, 0.3},
        {"pine", 400, 1.2}
    };
    int n=sizeof fruit/sizeof fruit[0];
    
    FILE* fp=fopen("15_10.out", "w");
    for (int i=0; i<n; i++){
        fprintf(fp, "%-6s %5d %6.1f\n", fruit[i].name, fruit[i].price, fruit[i].weight);
    }
    fclose(fp);
}