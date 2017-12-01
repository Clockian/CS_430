#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "parser.h"
#include "raycast.h"
#include "math3D.h"
#include "writer.h"

double construct_aspect_ratio(int width, int height){
	double aspect_ratio = (double) width / (double) height;
	return aspect_ratio;
}

void get_camera(int obj_count, scene_object objects[], scene_object *camera){
	for(int ii = 0; ii < obj_count; ii++){
		if(objects[ii].kind == 0){
			camera = &objects[ii];
		}
	}
}

void gamma_to_RGB(double r, double g, double b, Color *color){
	// Convert double to int, then store in char, and this works somehow...
	color->r = round(r * 255);
	color->g = round(g * 255);
	color->b = round(b * 255);
	}

double construct_V3_i(int i, double camera_width, int pixel_width){
	// The 0.0 represents the x or i coordinate of the center pixel of the screen
	// Equation pulled from in-class textbook
	// bug: camera_width pointer error, camera_width var replaced with 0.5 temporarily
	double Pi = 0.0 - (0.5 / 2.0)
					+ (0.5 / pixel_width)
					* (i + 0.5);
	return Pi;
}

double construct_V3_j(int j, double camera_height, int pixel_height){
	// The 0.0 represents the y or j coordinate of the center pixel of the screen
	// Equation pulled from in-class textbook, consider removing preceding - to flip y
	// See test, values don't make sense
	// bug: camera_width pointer error, camera_width var replaced with 0.5 temporarily
	double Pj = 0.0 - (0.5 / 2)
					+ (0.5 / pixel_height)
					* (j + 0.5);  // Apply aspect ratio?
	return Pj;
}

double construct_V3_z(void){
	double Pz = 1;  // or -1
	return Pz;
}

void normalize_ray(V3 *Rd){
	double Rd_magnitude = sqrt((Rd->i * Rd->i) + (Rd->j * Rd->j) + (Rd->z * Rd->z));
	V3_divide(Rd, Rd, Rd_magnitude);
}

double plane_intersection(V3* Ro, V3 *Rd, scene_object obj){
	int not_zero = 0;
	double t;
	double numerator;
	double denominator;

	V3 *difference = malloc(sizeof(V3));

	// Normal of plane
	V3 *Rn = malloc(sizeof(V3));
	Rn->i = obj.normal[0];
	Rn->j = obj.normal[1];
	Rn->z = obj.normal[2];
	normalize_ray(Rn);

	// Position of plane
	V3 *Rp = malloc(sizeof(V3));
	Rp->i = obj.position[0];
	Rp->j = obj.position[1];
	Rp->z = obj.position[2];

	denominator = V3_dot(Rd, Rn);
	//printf("%f\n", denominator);
	if(fabs(denominator) > 0.0001){
		// t = (Rp - Ro) * Rn / denominator
		V3_subtract(difference, Rp, Ro);
		numerator = V3_dot(difference, Rn);
		t = numerator/denominator;
		not_zero = 1;
	}

	free(difference);
	free(Rn);
	free(Rp);

	if(t >= 0 && not_zero == 1){
		return t;
	} else {
		return 1000000000000.0;  // return infinity
	}
}

double sphere_intersection(V3 *Ro, V3 *Rd, scene_object obj){
	double A;
	double B;
	double C;
	//double q;
	double t;
	double t0;
	double t1;
	double temp;
	double distance_sqrt;
	double discriminate;

	// 3D point of Sphere
	V3 *Rs = malloc(sizeof(V3));
	Rs->i = obj.position[0];
	Rs->j = obj.position[1];
	Rs->z = obj.position[2];
	
	V3 *difference_Ro_Rs = malloc(sizeof(V3));

	A = V3_dot(Rd, Rd);
	V3_subtract(difference_Ro_Rs, Ro, Rs);
	B = 2 * V3_dot(Rd, difference_Ro_Rs);
	C = V3_dot(difference_Ro_Rs, difference_Ro_Rs) - obj.radius * obj.radius;
	discriminate = (B * B) - (4 * A * C);

	free(Rs);
	free(difference_Ro_Rs);

	if(discriminate >= 0){
		distance_sqrt = sqrt(discriminate);
		t = (-0.5) * (B + distance_sqrt) / A;
		if(t > 0){
			return t;
		}
	}
	return 1000000000000.0;  // return infinity
}

double intersect(V3 *Ro, V3 *Rd, scene_object obj){
	if(obj.kind == 0){  // Camera, should return a result that is never true
		double t = 1000000000000.0;  // infinity
		return t;
	}
	if(obj.kind == 1){  // Sphere
		double t = sphere_intersection(Ro, Rd, obj);
		return t;
	}
	if(obj.kind == 2){  // Plane
		double t = plane_intersection(Ro, Rd, obj);
		return t;
	}
}

Color * raycast(V3 *Ro, V3 *Rd, Color *color, scene_object objects[], int obj_count){
	double t = 1000000000000.0;  // infinity
	double t_cur;
	scene_object closest_obj;
	scene_object obj;

	for(int ii = 0; ii < obj_count; ii++){
		obj = objects[ii];
		t_cur = intersect(Ro, Rd, obj);

		if(t_cur < t){
			t = t_cur;
			closest_obj = obj;
		}
	}

	if(t == 1000000000000.0){  // infinity
		gamma_to_RGB(0.0, 0.0, 0.0, color);
		return color;  // no intersection
	} else {
		// Passes back first interestion color
		gamma_to_RGB(closest_obj.color[0], closest_obj.color[1], closest_obj.color[2], color);
		return color;
	}
}

// Create function render(depends on whether or not you use global vars)
Color * render(int pixel_width, int pixel_height, scene_object objects[], int obj_count, Color *pixmap){
	V3 *Pijz = malloc(sizeof(V3));
	V3 *Rd = malloc(sizeof(V3));
	Color *color = malloc(sizeof(Color));
	scene_object *camera = malloc(sizeof(scene_object));

	V3 *Ro = malloc(sizeof(V3));
	Ro->i = 0;
	Ro->j = 0;
	Ro->z = 0;

	// Bug: Camera returns incorrect height and width
	get_camera(obj_count, objects, camera);
	//printf("camera->cam_width = %f, camera->cam_height = %f\n", camera->cam_width, camera->cam_height);

	for(int i = 0; i < pixel_height; i++){  // i from the Pij
		for(int j = 0; j < pixel_width; j++){
			// Construct Pijz
			Pijz->i = construct_V3_i(i, camera->cam_width, pixel_width);
			Pijz->j = construct_V3_j(j, camera->cam_height, pixel_height);
			Pijz->z = construct_V3_z();
			
			// Construct Rd, ray direction
			V3_subtract(Rd, Pijz, Ro);

			normalize_ray(Rd);

			// Cast the ray
			color = raycast(Ro, Rd, color, objects, obj_count);
			
			pixmap[(pixel_width * i) + j].r = color->r;
			pixmap[(pixel_width * i) + j].g = color->g;
			pixmap[(pixel_width * i) + j].b = color->b;
		}
	}

	free(Pijz);
	free(Rd);
	free(color);
	free(camera);
	free(Ro);

	return pixmap;
}