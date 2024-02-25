#include <stdio.h>
#include "load.h"
#include "print.h"

int main(int argc, char* argv[]){
    if (argc!=2){
        printf("Usage: %s in-csv\n", argv[0]);
        return 1;
    }
	POINTS* points=load_points(argv[1]);
	print_points(points);
	delete_points(points);
}