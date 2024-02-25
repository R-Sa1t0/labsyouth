#pragma once

typedef struct {
	double orig_x, orig_y, x, y;
	int cluster;
} POINT;

typedef struct {
	POINT* point;
	int count;
} POINTS;

POINTS* new_points(int count);
void delete_points(POINTS* points);