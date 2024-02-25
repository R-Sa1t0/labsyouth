#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "load.h"
#include "print.h"
#include "kmeans.h"

int main(int argc, char* argv[]){
	srand(time(NULL));
    if (argc!=3){
        printf("Usage: %s in-csv clusters\n", argv[0]);
        return 1;
    }
    POINTS* points=load_points(argv[1]);
    POINTS* centroids=kmeans(points, atoi(argv[2]));

	puts("result(points):");
	print_points(points);

	puts("result(centroids):");
	print_points(centroids);

	delete_points(points);
	delete_points(centroids);
}