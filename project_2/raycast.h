#ifndef RAYCAST_H
#define RAYCAST_H

#include "parser.h"
#include "writer.h"
//#include "math3D.h"

typedef struct{
	double i, j, z;
}V3;

double construct_aspect_ratio(int width, int height);

double construct_V3_i(int i, int width, int height);

double construct_V3_j(int j, int width, int height);

double construct_V3_z(void);

V3 * construct_V3_i_j_z(int i, int j, int width, int height);

V3 * construct_ray_direction(V3 *Pijz);

V3 * normalize_ray(V3 *Rd);

double plane_intersection(V3 *Rd, scene_object obj);

double sphere_intersection(V3 *Rd, scene_object obj);

double intersect(V3 *Rd, scene_object obj);

Pixel * raycast(V3 *Rd, scene_object objects[], int obj_count);

Pixel * render(int width, int height, scene_object objects[], int obj_count);

#endif /* RAYCAST_H */