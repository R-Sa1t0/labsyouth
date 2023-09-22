#include <stdio.h>

int main(){
    {
        int sales[5];
        
        printf("%lu\n", sizeof sales);
        printf("%lu\n", sizeof sales[0]);
        printf("%lu\n", sizeof sales / sizeof sales[0]);

        for (int i=0; i<5; i++) printf("%p\n", &sales[i]);
    }
    {
        int sales[]={190, 280, 370, 460, 550};
        for (int i=0; i<5; i++) printf("%d ", sales[i]);
        puts("");
    }
    {
        int sales[]={[2]=190, 280, [0]=370, 460, 550};
        for (int i=0; i<5; i++) printf("%d ", sales[i]);
        puts("");
    }
    {
        int sales[5]={190, 280, 370};
        for (int i=0; i<5; i++) printf("%d ", sales[i]);
        puts("");
    }
    {
        int sales[5]={[2]=190, [0]=280};
        for (int i=0; i<5; i++) printf("%d ", sales[i]);
        puts("");
    }
}