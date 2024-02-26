#include <stdio.h>

void print_p(int* p){
    while (*p) printf("%d\n", *p++);
}
void print_arr(int a[]){
    for (int i=0; a[i]; i++) printf("%d\n", a[i]);
}

int char_len(char* s){
    char* p=s;
    while(*p) p++;
    return p-s;
}
void char_cpy(char* to, char* from){
    while (*from) *to++=*from++;
    *to='\0';
}

int main(){
    int x;
    int* p0=&x;
    printf("%p\n", &x);
    printf("%p\n", p0);

    *p0=456;
    printf("%d\n", x);
    printf("%d\n", *p0);

    int* p_null=NULL;
    printf("%p\n", p_null);

    int bottle[]={300,500,700,1000,1500,0};
    int* p1=bottle;
    printf("%p\n", bottle);
    printf("%p\n", p1);
    for (int i=0; *(p1+i); i++) printf("%p %d\n",p1+i,*(p1+i));
    for (int i=0; p1[i]; i++) printf("%d\n", p1[i]);
    for (int i=0; i[p1]; i++) printf("%d\n", i[p1]);
    for (int* p=bottle; *p; p++) printf("%d\n", *p);
    print_p(bottle);
    print_arr(bottle);

    printf("%d\n", char_len("Hello!"));
    char s[100];
    char_cpy(s, "Hello!");
    puts(s);
}