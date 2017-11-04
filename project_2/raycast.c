#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "parser.h"
#include "raycast.h"

double construct_aspect_ratio(int width, int height){
	double aspect_ratio = (double) width / (double) height;
	return aspect_ratio;
}

double construct_V3_i(int i, int width, int height){
	double Pi = ((double) i / ((double) width * 0.5)) - 1;
	Pi = Pi / construct_aspect_ratio(width, height);
	return Pi;
}

double construct_V3_j(int j, int height){
	double Pj = 1 - ((double) j / ((double) height * 0.5));
	return Pj;
}

// IDK, Z axis seems like it shouldn't be this, but some tan formula... idk
double construct_V3_z(void){
	double Pz = -1;
	return Pz;
}

V3 * construct_V3_i_j_z(int i, int j, int width, int height){
	V3 *Pijz = malloc(sizeof(V3));
	
	Pijz->i = construct_V3_i(i, width, height);
	Pijz->j = construct_V3_j(j, height);
	Pijz->z = construct_V3_z();

	return Pijz;
}

V3 * construct_ray_direction(V3 *Pijz){
	V3 *Rd = malloc(sizeof(V3));

	Rd->i = Pijz->i - 0;
	Rd->j = Pijz->j - 0;
	Rd->z = Pijz->z - 0;

	return Rd;
}

V3 * normalize_ray(V3 *Rd){
	V3 *normalized_Rd = malloc(sizeof(V3));

	double Rd_magnitude = sqrt((Rd->i * Rd->i) + (Rd->j * Rd->j) + (Rd->z * Rd->z));

	normalized_Rd->i = Rd->i / Rd_magnitude;
	normalized_Rd->j = Rd->j / Rd_magnitude;
	normalized_Rd->z = Rd->z / Rd_magnitude;

	return normalized_Rd;
}

//intersection(){

//}

// Create function render(depends on whether or not you use global vars)
V3 * render(int width, int height){
	
	V3 *Pijz = malloc(sizeof(V3));
	V3 *Rd = malloc(sizeof(V3));
	//pixel *pixels = malloc(sizeof(pixel));

	for(int i = 0; i < width; i++){  // i from the Pij
		for(int j = 0; j < height; j++){

			Pijz = construct_V3_i_j_z(i, j, width, height);

			Rd = construct_ray_direction(Pijz);

			Rd = normalize_ray(Rd);

			// Cast the ray
			//color = raycast(Ro, Rd, ...);

			// Colors in ray tracers go from 0-1, RGB is 1-255, need conversion
			//pixels[...] = color.red;
			//pixles[...] = color.green;
			//pixels[...] = color.blue;
		}
	}
}

void Raycast(){//Ro, Rd){
	/*cloest_obj = NULL;
	closet_t = 10000; //infinity, set to very large number

	// while loop might be better
	for(int i = 0; i < object_count; i += 1){
		obj = objects[i];

		// Test for what kind of object it is
		double t = intersection(Ro, Rd, obj);
		double t;
		
		// For sphere, not just intersection, but sphere intersection
		// Code may replace code above
		if(obj.kind == SPHERE){
			double t = sphere_intersection(Ro, Rd, obj);
		}
		if(obj.kind == PLANE){
			double t = plane_intesection(Ro, Rd, obj);
		}
	}
	// Closest_obj == null?
	if(t < closest_t){
		closest_t = t;
		closest_obj = obj;
	}

	// Passes back last color, need to pass first color, which above achieves?
	return closet_obj.color;*/
}