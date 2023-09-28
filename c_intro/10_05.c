#include <stdio.h>

double avg(int a[]){
    int total=0, i;
    for (i=0; a[i]>=0; i++) total += a[i];
    return (double)total/i; 
}

int main(){
    int score[]={84, 93, 100, 75, 64, -1};
    printf("%g\n", avg(score));
    //printf("%g\n", avg((int[]){84, 93, 100, 75, 64, -1}));
}