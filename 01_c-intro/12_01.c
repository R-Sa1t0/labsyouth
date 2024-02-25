#include <stdio.h>

struct fruit
{
    char name[100];
    int price;
    double weight;
};

typedef struct
{
    char name[100];
    int price;
    double weight;
} FRUIT;

void print(FRUIT f){
    printf("%s, %d yen, %g kg\n", f.name, f.price, f.weight);
}
FRUIT input(){
    FRUIT f;
    printf("name price weight : ");
    scanf("%s%d%lf", &f.name, &f.price, &f.weight);
    return f;
}


int main(){
    struct fruit a={"apple", 150, 0.4};
    printf("a : %s, %d yen, %g kg\n", a.name, a.price, a.weight);
    
    FRUIT b={"apple", 150, 0.4};
    printf("b : %s, %d yen, %g kg\n", b.name, b.price, b.weight);

    // 真ん中がまぎらわしいかも
    FRUIT c={.price=105, 0.4, .name="apple"};
    printf("c : %s, %d yen, %g kg\n", c.name, c.price, c.weight);

    FRUIT d=b;
    d.price/=2;
    d.weight*=0.7;
    printf("d : %s, %d yen, %g kg\n", d.name, d.price, d.weight);

    print(b);
    print(d);

    print((FRUIT){"apple", 150, 0.4});
    print(input());

    FRUIT f[]={
        {"Apple", 150, 0.4},
        {"banana", 20, 0.2},
        {"kiwi", 130, 0.1},
        {"melon", 900, 2.0},
        {"orange", 100, 0.3},
        {"pine", 400, 1.2}
    };
    int n=sizeof f/sizeof f[0];
    puts("name price weight");
    for (int i=0; i<n; i++) printf("%-6s %5d %6.1f\n", f[i].name, f[i].price, f[i].weight);
}