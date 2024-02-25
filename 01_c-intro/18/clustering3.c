#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "load.h"
#include "print.h"
#include "kmeans.h"
#include "plot.h"

int main(int argc, char* argv[]){
    srand(time(NULL));
	if (argc!=4) {
		printf("usage: %s in-csv out-html clusters\n", argv[0]);
		return 1;
	}

	POINTS* points=load_points(argv[1]);
	POINTS* centroids=kmeans(points, atoi(argv[3]));

	puts("result(points):");
	print_points(points);

	puts("result(centroids):");
	print_points(centroids);

	plot_points(points, centroids, argv[2]);
    
	delete_points(points);
	delete_points(centroids);
}