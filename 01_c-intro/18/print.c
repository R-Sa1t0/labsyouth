#include <stdio.h>
#include "print.h"

void print_points(POINTS* points){
    printf("%15s %15s %10s %10s %10s \n", "original-x", "original-y", "x", "y", "cluster");
    for (int i=0; i<points->count; i++){
		POINT* p=&points->point[i];
		printf("%15.2f %15.2f %10.2f %10.2f %10d\n", p->orig_x, p->orig_y, p->x, p->y, p->cluster);
	}
    printf("number of points: %d\n\n", points->count);
}