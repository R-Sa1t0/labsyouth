#include <stdio.h>
int zzz=999;

void f(int x){
    x++;
}
void f_arr(int i[]){
    i[0]++;
}
int len(char s[]){
    int i;
    for (i=0; s[i]; i++);
    return i;
}
void strcpy_(char to[], char from[]){
    int i;
    for (i=0; from[i]; i++) to[i] = from[i];
    to[i]='\n';
}
void scope_test(){
    int z=100;
    printf("%d\n", z);
}
void print_global(){
    printf("%d\n", zzz);
}
void edit_global(){
    zzz++;
    printf("%d\n", zzz);
}
void count(){
    int count=0;
    printf("%d\n", ++count);
}

int main(){
    int x=0;
    printf("%d\n", x);
    f(x);
    printf("%d\n", x);

    int y[]={0};
    printf("%d\n", y[0]);
    f_arr(y);
    printf("%d\n", y[0]);

    printf("%d\n", len("String Length"));

    char s[100];
    strcpy_(s, "String Cpy");
    puts(s);

    int z=200;
    printf("%d\n", z);
    scope_test();
    printf("%d\n", z);

    printf("%d\n", zzz);
    print_global();

    printf("%d\n", zzz);
    edit_global();

    count();
    count();
    count();
}