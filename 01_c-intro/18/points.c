#include <stdlib.h>
#include "points.h"

POINTS* new_points(int count){
    POINTS* points = malloc(sizeof(POINTS));
    *points = (POINTS){malloc(count*sizeof(POINT)), count};
    return points;
}

void delete_points(POINTS* points){
    free(points->point);
    free(points);
}