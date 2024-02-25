#include <stdio.h>

typedef struct
{
    char name[100];
    int price;
    double weight;
} FRUIT;

int main(){
    FRUIT fruit[100];
    int n=0;

    FILE* fp=fopen("15_10.out", "r");
    while (fscanf(fp, "%s%d%lf", fruit[n].name, &fruit[n].price, &fruit[n].weight)!=EOF){
        //if (++n>=sizeof fruit/sizeof fruit[0]) break;
        // warning: comparison of integers of different signs: 'int' and 'unsigned long' [-Wsign-compare]
        if (++n>=(int)sizeof fruit/(int)sizeof fruit[0]) break;
    }
    fclose(fp);

    for (int i=0; i<n; i++){
        printf("%-6s %5d %6.1f\n", fruit[i].name, fruit[i].price, fruit[i].weight);
    }
}