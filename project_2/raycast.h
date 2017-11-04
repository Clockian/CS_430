#ifndef RAYCAST_H
#define RAYCAST_H

typedef struct{
	double i, j, z;
}V3;

double construct_aspect_ratio(int width, int height);

double construct_V3_i(int i, int width, int height);

double construct_V3_j(int j, int height);

double construct_V3_z(void);

V3 * construct_V3_i_j_z(int i, int j, int width, int height);

V3 * construct_ray_direction(V3 *Pijz);

V3 * normalize_ray(V3 *Rd);

V3 * render(int width, int height);

void Raycast();

#endif /* RAYCAST_H */