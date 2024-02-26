#include <stdio.h>

double avg(int a[], int n){
    // f(int a[])だと先頭アドレスは渡るけど長さは渡らない -> 長さを渡す
    printf("%p\n", a);
    printf("%lu\n", sizeof a);

    int total = 0;
    for (int i=0; i<n; i++) total += a[i];

    return (double)total/n;
}

int main(void){
    int score[]={84, 93, 100, 75, 64};
    printf("%p\n", score);
    printf("%lu\n", sizeof score);

    printf("%g\n", avg(score, sizeof score/sizeof score[0]));
}