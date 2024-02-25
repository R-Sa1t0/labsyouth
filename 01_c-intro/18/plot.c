#include <stdio.h>
#include <stdlib.h>
#include "plot.h"

void plot_points(POINTS* points, POINTS* centroids, const char* file){
    FILE* fp=fopen(file, "w");
    if (!fp) {
        printf("Can't open %s\n", file);
        exit(1);
    }

    fputs("<!DOCTYPE html>\n<html>\n<body>\n", fp);

    int w=1000, h=1000, size=10;
    fprintf(fp, "<svg width=%d height=%d>\n", w+size*4, h+size*4);
	fprintf(fp, "<rect width=%d height=%d " "fill=\"white\" stroke=\"black\"/>", w+size*4, h+size*4);

    for (int i=0; i<centroids->count; i++) {
		POINT* c=&centroids->point[i];
		int r=rand()%256, g=rand()%256, b=rand()%256;
		for (int j=0; j<points->count; j++) {
			POINT* p=&points->point[j];
			if (p->cluster!=i) continue;
			fprintf(fp, "<circle cx=%d cy=%d r=%d " "fill=rgb(%d,%d,%d) stroke=\"black\">", (int)(p->x*w)+size*2, h-(int)(p->y*h)+size*2, size, r, g, b);
			fprintf(fp, "<title>(%.2f, %.2f)</title></circle>", p->orig_x, p->orig_y);
		}
		
        fprintf(fp, "<rect x=%d y=%d width=%d height=%d " "fill=rgb(%d,%d,%d) stroke=\"black\">\n", (int)(c->x*w)+size/2, h-(int)(c->y*h)+size/2,  size*3, size*3, r, g, b);
		
        fprintf(fp, "<title>(%.2f, %.2f)</title></rect>", c->orig_x, c->orig_y);
	}

	fputs("</svg>\n</body>\n</html>\n", fp);
	fclose(fp);
}