#include <stdio.h>

typedef union{
    int i;
    char c[4];
} INT_CHAR;

typedef struct {
    unsigned short r, g, b;
} COLOR_ST;
typedef struct {
    unsigned int r:10, g:10, b:10;
} COLOR_BF;


int main(){
    INT_CHAR a={0x12345678};
    printf("%x\n", a.i);
    char b;
    b=a.c[0], a.c[0]=a.c[3], a.c[3]=b;
    b=a.c[1], a.c[1]=a.c[2], a.c[2]=b;
    printf("%x\n", a.i);
    puts("");

    printf("%lu\n", sizeof(COLOR_ST));
    printf("%lu\n", sizeof(COLOR_BF));
    puts("");

    for(;;){
        double r,g,b;
        printf("r g b : ");
        scanf("%lf%lf%lf", &r, &g, &b);

        r = r>1 ? 1 : r<0 ? 0 : r;
        g = r>1 ? 1 : g<0 ? 0 : g;
        b = r>1 ? 1 : b<0 ? 0 : b;
        
        COLOR_BF c={r*1023, g*1023, b*1023};
        printf("%d %d %d\n", c.r, c.g, c.b);
    }
}