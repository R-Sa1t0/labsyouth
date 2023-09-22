#include <stdio.h>

int main(){
    // 出力が続いてしまう
    {
        int x,y;
        scanf("%d%d", &x, &y);
        for(int i=1; i<=9; i++){
            for(int j=1; j<=9; j++){
                printf("%2d ", i*j);
                if (i==x && j==y) break;
            } 
            puts("");
        }
        puts("");
    }
    // gotoを使うと出力が止められる
    {
        int x,y;
        scanf("%d%d", &x, &y);
        for(int i=1; i<=9; i++){
            for(int j=1; j<=9; j++){
                printf("%2d ", i*j);
                if (i==x && j==y) goto end;
            } 
            puts("");
        }
        end:
            puts("");
    }
    // goto
    {
        int price, count;
    
        printf("price : ");
        scanf("%d", &price);
        if (price<0) goto error;

        printf("count : ");
        scanf("%d", &count);
        if (count < 0) goto error;

        printf("total : %d\n", price*count);
        goto end;

        error: 
            puts("error!");
        end:
            puts("Thank you!");
    }
    {
        int price, count;
        
        printf("price : ");
        scanf("%d", &price);
        if(price>=0){
            printf("count : ");
            scanf("%d", count);
            if(count>=0) printf("total : %d\n", price*count);
        }

        if (price<0 || count<0) puts("error!");
        puts("Thank you.");
    }
}