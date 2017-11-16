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

double plane_intersection(V3 *Rd, scene_object obj){
	// Origin of camera
	V3 *Ro = malloc(sizeof(V3));
	Ro->i = 0;
	Ro->j = 0;
	Ro->z = 0;

	// Normal of plane
	V3 *Rn = malloc(sizeof(V3));
	Rn->i = obj.normal[0];
	Rn->j = obj.normal[1];
	Rn->z = obj.normal[2];
	Rn = normalize_ray(Rn);

	// Position of plane
	V3 *Rp = malloc(sizeof(V3));
	Rp->i = obj.position[0];
	Rp->j = obj.position[1];
	Rp->z = obj.position[2];

	double t;

	double denominator = V3_dot(Rd, Rn);

	if(fabs(denominator) < 0.000001){
		return 1000000000000; //return infinity
	}

	// Get a vector of the plane
	V3 *plane = malloc(sizeof(V3));
	V3_subtract(plane, Rp, Ro);

	double numerator = V3_dot(Rn, plane);

	t = numerator/denominator;

	if(t < 0){
		return 1000000000000;
	}

	return t;

	/*if(denominator > 0){
		//normal times (point on plane minus ray origin)
		// (point on plane minus ray origin)
		V3 *plane = malloc(sizeof(V3));
		V3_subtract(plane, Rp, Ro);
		double numerator = V3_dot(Rn, plane);
		t = numerator/denominator;

		if (t >= 0){
			V3 *result = malloc(sizeof(V3));
			V3_multiply(result, Rd, t);
			return t;
		}
	}
	return 0;*/
}

double sphere_intersection(V3 *Rd, scene_object obj){
	//printf("Rd = %f, %f, %f\n", Rd->i, Rd->j, Rd->z);
	V3 *Ro = malloc(sizeof(V3));
	Ro->i = 0.0;
	Ro->j = 0.0;
	Ro->z = 0.0;

	double A = (Rd->i * Rd->i) + (Rd->j * Rd->j) + (Rd->z * Rd->z);
	//double B = 2 * (Rd->i * (0 - obj.position[0]) + 
	//	        Rd->j * (0 - obj.position[1]) + 
	//	        Rd->z * (0 - obj.position[2]));
	double B = (2 * Rd->i * (0 - obj.position[0]) + 
		        2 * Rd->j * (0 - obj.position[1]) + 
		        2 * Rd->z * (0 - obj.position[2]));
	//double B = 2 * V3_dot(Rd, Ro);
	double C = ((Rd->i - obj.position[0]) * (Rd->i - obj.position[0]) +
	            (Rd->j - obj.position[1]) * (Rd->j - obj.position[1]) +
	            (Rd->z - obj.position[2]) * (Rd->z - obj.position[2]) -
	            (obj.radius * obj.radius));

	double discriminate = (B * B) - (4 * A * C);

	double intersect;
	double intersect_1;
	double intersect_2;
	//printf("B  = %f\nA  = %f\nC  = %f\n", B, A, C);
	//printf("discriminate - %f\n", discriminate);
	if(discriminate < 0){
		return -1;
	} else if(discriminate == 0){
		// Single intersection
		intersect = (-B)/(2 * A);
	} else if(discriminate > 0){
		intersect_1 = ((-B - sqrt((B * B) - (4 * A * C))) / (2 * A));
		intersect_2 = ((-B + sqrt((B * B) - (4 * A * C))) / (2 * A));
		if(intersect_1 >= 0 && intersect_1 < intersect_2){
			intersect = intersect_1;
		} else {
			intersect = intersect_2;
		}
	} else{
		printf("Error: sphere_intersection\n");
	}

	//Compute intersection
	//V3 Ri = malloc(sizeof(V3));
	//Ri.i = 0 + (Rd->i * intersect);
	//Ri.j = 0 + (Rd->j * intersect);
	//Ri.z = 0 + (Rd->z * intersect);
	//printf("intersect - %f\n", intersect);
	return intersect;
}

Pixel * raycast(V3 *Rd, scene_object objects[], int obj_count){//Ro, Rd){
	scene_object closest_obj;
	int closest_t = 1000; //infinity, set to very large number
	double t;
	double t_store[obj_count];
	scene_object obj;
	// while loop might be better
	for(int i = 0; i < obj_count; i++){
		obj = objects[i];

		// Test for what kind of object it is
		//double t = intersection(Ro, Rd, obj);
		
		// For sphere, not just intersection, but sphere intersection
		// Code may replace code above
		if(obj.kind == 1){ //one is sphere
			t = sphere_intersection(Rd, obj);
		}
		if(obj.kind == 2){ //two is plane
			t = plane_intersection(Rd, obj);
		}

		// Closest_obj == null?
		//if(t < closest_t){
		//	closest_t = t;
			closest_obj = obj;
		//}
	}

	Pixel *color = malloc(sizeof(Pixel));

	int r = round(closest_obj.color[0] * 255);
	int g = round(closest_obj.color[1] * 255);
	int b = round(closest_obj.color[2] * 255);

	color->r = *((unsigned char *)&r);
	color->g = *((unsigned char *)&g);
	color->b = *((unsigned char *)&b);

	// Passes back last color, need to pass first color, which above achieves?
	return color;
}

// Create function render(depends on whether or not you use global vars)
Pixel * render(int width, int height, scene_object objects[], int obj_count){
	
	V3 *Pijz = malloc(sizeof(V3));
	V3 *Rd = malloc(sizeof(V3));
	Pixel *pixmap = malloc(sizeof(Pixel) * width * height);
	Pixel *color;

	for(int i = 0; i < height; i++){  // i from the Pij
		for(int j = 0; j < width; j++){

			Pijz = construct_V3_i_j_z(i, j, width, height);

			Rd = construct_ray_direction(Pijz);

			Rd = normalize_ray(Rd);

			// Cast the ray
			color = raycast(Rd, objects, obj_count);
			
			pixmap[(width * i) + j].r = color->r;
			pixmap[(width * i) + j].g = color->g;
			pixmap[(width * i) + j].b = color->b;
			
			//pixmap[(width * i) + j].r = 0;//color->r;
			//pixmap[(width * i) + j].g = 255;//color->g;
			//pixmap[(width * i) + j].b = 255;//color->b

			// Colors in ray tracers go from 0-1, RGB is 1-255, need conversion
			//pixels[...] = color.red;
			//pixles[...] = color.green;
			//pixels[...] = color.blue;
		}
	}
	return pixmap;
}