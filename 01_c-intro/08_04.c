#include <stdio.h>

int main(){
    {
        enum { ROW=2, COL=3 };
        int a[ROW][COL] = {{11,12,13},{21,22,23}};
        
        for (int i=0; i<ROW; i++){
            for (int j=0; j<COL; j++) printf("%d ", a[i][j]);
            puts("");
        }
    }
    puts("");
    {
        enum { ROW=2, COL=3 };
        int a[ROW*COL] = {11,12,13,21,22,23};

        for (int i=0; i<ROW; i++){
            for (int j=0; j<COL; j++) printf("%2d ", a[i*COL+j]);
            puts("");
        }
    }
    puts("");
}