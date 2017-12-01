#ifndef RAYCAST_H
#define RAYCAST_H

#include "parser.h"
#include "writer.h"

typedef struct{
	double i, j, z;
}V3;

double construct_aspect_ratio(int width, int height);

void get_camera(int obj_count, scene_object objects[], scene_object *camera);

void gamma_to_RGB(double r, double g, double b, Color *color);

double construct_V3_i(int i, double camera_width, int pixel_width);

double construct_V3_j(int j, double camera_height, int pixel_height);

double construct_V3_z(void);

void normalize_ray(V3 *Rd);

double plane_intersection(V3 *Ro, V3 *Rd, scene_object obj);

double sphere_intersection(V3 *Ro, V3 *Rd, scene_object obj);

double intersect(V3 *Ro, V3 *Rd, scene_object obj);

Color * raycast(V3 *Ro, V3 *Rd, Color *color, scene_object objects[], int obj_count);

Color * render(int pixel_width, int pixel_height, scene_object objects[], int obj_count, Color *pixmap);

#endif /* RAYCAST_H */