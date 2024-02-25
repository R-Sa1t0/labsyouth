#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "print.h"
#include "kmeans.h"

POINTS* kmeans(POINTS* points, int num_clusters){
    POINTS* centroids = new_points(num_clusters);
    POINTS* old_centroids = new_points(num_clusters);

    for (int i=0; i<centroids->count; i++){
        centroids->point[i]=points->point[rand()%points->count];
    }

    for (int n=0;;n++){
        printf("iteration %d:\n", n);
        print_points(centroids);
        
        for (int i=0; i<points->count; i++){
            POINT* p=&points->point[i];
            double min_dist=INFINITY;
            for (int j=0; j<centroids->count; j++){
                POINT* c=&centroids->point[j];
                double dist=pow(p->x-c->x, 2)+pow(p->y-c->y, 2);
                if (dist<min_dist)min_dist=dist, p->cluster=j;
            }
        }

        for (int i=0; i<centroids->count; i++){
            old_centroids->point[i]=centroids->point[i];
            centroids->point[i]=(POINT){0, 0, 0, 0, 0};
        }

        for (int i=0; i<points->count; i++){
            POINT* p=&points->point[i];
            POINT* c=&centroids->point[p->cluster];
            c->orig_x+=p->orig_x, c->orig_y+=p->orig_y;
            c->x+=p->x, c->y+=p->y, c->cluster++;
        }

        int moved=0;
        for (int i=0; i<centroids->count; i++){
            POINT* c=&centroids->point[i];
            int n=c->cluster;
            if (n){
                c->orig_x/=n, c->orig_y/=n;
                c->x/=n, c->y/=n;
            }
            POINT* oc=&old_centroids->point[i];
            if (c->x!=oc->x || c->y!=oc->y)moved=1;
        }
        if (!moved)break;
    }
    delete_points(old_centroids);
    return centroids;
}
