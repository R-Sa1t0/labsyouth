#include <stdio.h>
#include <stdlib.h>

int compare(const void* p, const void* q){
    return *(int*)p-*(int*)q;
}
int compare2(const void* p, const void* q){
    return *(int*)q-*(int*)p;
}

int main(){
    int a[]={84,93,100,75,64};
    int n=sizeof a/sizeof a[0];

    qsort(a, n, sizeof a[0], compare);
    for (int i=0; i<n; i++) printf("%d ", a[i]);
    puts("");

    qsort(a, n, sizeof a[0], compare2);
    for (int i=0; i<n; i++) printf("%d ", a[i]);
    puts("");
}