#ifndef RAYCAST_H
#define RAYCAST_H

typedef struct{
	double i, j, z;
}pixel;

double construct_aspect_ratio(int width, int height);

double construct_pixel_i(int i, int width, int height);

double construct_pixel_j(int j, int height);

double construct_pixel_z(void);

pixel * construct_pixel_i_j_z(int i, int j, int width, int height);

pixel * construct_ray_direction(pixel *Pijz);

pixel * normalize_ray(pixel *Rd);

#endif /* RAYCAST_H */