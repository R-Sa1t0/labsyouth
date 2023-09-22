#include <stdio.h>

int main(){
    int n;
    printf("count : ");
    scanf("%d", &n);
    
    int sales[n];
    for (int i=0; i<n; i++) scanf("%d", &sales[i]);
    puts("");

    int total=0;
    for (int i=0; i<n; i++) total+=sales[i];

    puts("sales percentage");
    for (int i=0; i<n; i++){
        printf("%5d %9.1f%%\n", sales[i], sales[i]*100.0/total);
    }
}