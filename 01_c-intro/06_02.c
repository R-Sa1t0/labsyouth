#include <stdio.h>

int main(){
    {
        int t;
        printf("temp : ");
        scanf("%d", &t);

        if (t>30) puts("cooler");
        else if (t<20) puts("heater");
        else puts("off");

        if (t>30){
            puts("cooler");
        }else if(t<20){
            puts("heater");
        }else{
            puts("off");
        }

        puts(t>30 ? "cooler" : t<20 ? "heater" : "off");
    }
    {
        int price, rank;
        printf("price and rank : ");
        scanf("%d%d", &price, &rank);

        switch (rank){
        case 1:
            price *= 0.8;
            break;
        case 2:
            price *= 0.9;
            break;
        default:
            price *= 0.95;
            break;
        }
        printf("discount price : %d\n", price);
    }
    {
        int menu;
        printf("menu : ");
        scanf("%d", &menu);
        switch (menu){
        case 2: puts("dessert");
        case 1: puts("coffee");
        default: puts("steak");
        }
    }
}