#include <stdio.h>
#include <string.h>

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
    for (;;){
        char name[100];
        double weight;
        printf("name and weight : ");
        scanf("%s%lf", name, &weight);
        for (int i=0; i<n; i++){
            if (strcmp(fruit[i].name, name)==0){
                int price = fruit[i].price*weight/fruit[i].weight;
                printf("price : %d\n\n", price);
                break;
            }
        }
    }  

}