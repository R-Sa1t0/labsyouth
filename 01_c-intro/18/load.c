#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "load.h"

POINTS* load_points(const char* file){
	char s[1000];
	FILE* fp=fopen(file, "r");
	if (!fp) {
		printf("Can't open %s\n", file);
		exit(1);
	}

	int n=0;
	while (fgets(s, sizeof s, fp)) {
		if (isdigit(s[0])) n++;
	}
	POINTS* points=new_points(n);

    rewind(fp);
    for (POINT* p=points->point; fgets(s, sizeof s, fp); ){
        if (fscanf(fp, "%lf,%lf", &p->x, &p->y)!=2) continue;
		p->orig_x=p->x, p->orig_y=p->y, p->cluster=0, p++;
    }
    fclose(fp);

    double min_x, min_y, max_x, max_y;
    min_x = min_y = INFINITY, max_x = max_y = -INFINITY;
    for (int i=0; i<points->count; i++){
        POINT* p = &points->point[i];
        min_x = fmin(min_x, p->x), min_y = fmin(min_y, p->y);
        max_x = fmax(max_x, p->x), max_y = fmax(max_y, p->y);
    }
    for (int i=0; i<points->count; i++){
        POINT* p = &points->point[i];
        p->x=max_x-min_x ? (p->x-min_x)/(max_x-min_x) : 0.5;
        p->y=max_y-min_y ? (p->y-min_y)/(max_y-min_y) : 0.5;
    }

    return points;
}