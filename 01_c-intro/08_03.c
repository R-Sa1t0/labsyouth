#include <stdio.h>
#include <string.h>

int main(){
    {
        enum {N=5};
        int sales_a[] = {190, 280, 370, 460, 550};
        int sales_b[N];
        for (int i=0; i<N; i++) sales_b[i] = sales_a[i];

        for (int i=0; i<N; i++) printf("%d ", sales_a[i]);
        puts("");
        for (int i=0; i<N; i++) printf("%d ", sales_a[i]);
        puts("");
    }
    {
        enum {N=5};
        int sales_a[] = {190, 280, 370, 460, 550};
        int sales_b[N];
        memcpy(sales_b, sales_a, sizeof sales_b);

        for (int i=0; i<N; i++) printf("%d ", sales_a[i]);
        puts("");
        for (int i=0; i<N; i++) printf("%d ", sales_a[i]);
        puts("");
    }
    

}