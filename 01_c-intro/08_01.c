#include <stdio.h>

int main(){
/*
    {
        int arr[5];

        scanf("%d", &arr[0]);
        scanf("%d", &arr[1]);
        scanf("%d", &arr[2]);
        scanf("%d", &arr[3]);
        scanf("%d", &arr[4]);

        printf("%d\n", arr[0]);
        printf("%d\n", arr[1]);
        printf("%d\n", arr[2]);
        printf("%d\n", arr[3]);
        printf("%d\n", arr[4]);
    }
    {
        int arr[5];
        for (int i=0; i<5; i++) scanf("%d", &arr[i]);
        for (int i=0; i<5; i++) printf("%d\n", arr[i]);
    }
    {
        #define N_def 5
        int arr[N_def];
        for (int i=0; i<N_def; i++) scanf("%d", &arr[i]);
        for (int i=0; i<N_def; i++) printf("%d\n", arr[i]);
    }
    {
        enum { N_enum=5 };
        int arr[N_enum];
        for (int i=0; i<N_enum; i++) scanf("%d", &arr[i]);
        for (int i=0; i<N_enum; i++) printf("%d\n", arr[i]);
    }
*/
    {
        enum { N=5 };
        int sales[N];
        for (int i=0; i<N; i++) scanf("%d", &sales[i]);
        for (int i=0; i<N; i++) printf("%d\n", sales[i]);
        
        int sum=0;
        for (int i=0; i<N; i++) sum+=sales[i];

        // ".0"を忘れない
        puts("sales percentage");
        for (int i=0; i<N; i++) printf("%5d %9.1f%%\n", sales[i], sales[i]*100.0/sum);
    }
}