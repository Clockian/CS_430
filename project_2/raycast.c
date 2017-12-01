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
	double Pi = 0.0 - (0.5 / 2.0) + (0.5 / width) * (i + 0.5);
	return Pi;

	//double Pi = ((double) i / (double) width) - 0.5;  // alt source says +0.25, assume FOV 90 -> 45, thus * 1
	//return Pi;

	//double Pi = ((double) i / ((double) width * 0.5)) - 1;
	//Pi = Pi / construct_aspect_ratio(width, height);
	//return Pi;
}

double construct_V3_j(int j, int width, int height){
	double Pj = 0.0 - (0.5 / 2) + (0.5 / height) * (j + 0.5);
	return Pj;

	//double Pj = ((double) j / (double) height) - 0.5;  // alt source says +0.25
	//double aspect = construct_aspect_ratio(width, height);
	//Pj = Pj / aspect;
	//Pj = -Pj;
	//return Pj;
	
	//double Pj = 1 - ((double) j / ((double) height * 0.5));
	//return Pj;
}

// IDK, Z axis seems like it shouldn't be this, but some tan formula... idk
double construct_V3_z(void){
	double Pz = 1;
	//double Pz = -1;
	return Pz;
}

V3 * construct_V3_i_j_z(int i, int j, int width, int height){
	V3 *Pijz = malloc(sizeof(V3));
	
	Pijz->i = construct_V3_i(i, width, height);
	Pijz->j = construct_V3_j(j, width, height);
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

	V3_divide(normalized_Rd, Rd, Rd_magnitude);
	//normalized_Rd->i = Rd->i / Rd_magnitude;
	//normalized_Rd->j = Rd->j / Rd_magnitude;
	//normalized_Rd->z = Rd->z / Rd_magnitude;

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

	double distance;

	double denominator = V3_dot(Rd, Rn);

	if(fabs(denominator) < 0.000001){
		return 1000000000000.0;  // return infinity
	}

	// Get a vector of the plane
	V3 *difference = malloc(sizeof(V3));

	V3_subtract(difference, Rp, Ro);

	double numerator = V3_dot(difference, Rn);

	distance = numerator/denominator;

	if(distance < 0){
		return 1000000000000.0;  // return infinity
	}
	return distance;

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
	// Origin of Camera
	V3 *Ro = malloc(sizeof(V3));
	Ro->i = 0.0;
	Ro->j = 0.0;
	Ro->z = 0.0;

	// 3D point of Sphere
	V3 *Rs = malloc(sizeof(V3));
	Rs->i = obj.position[0];
	Rs->j = obj.position[1];
	Rs->z = obj.position[2];

	V3 *difference_Ro_Rs = malloc(sizeof(V3));

	double A;
	double B;
	double C;
	//double q;
	double t;
	double t0;
	double t1;
	double temp;
	double distance_sqrt;

	A = V3_dot(Rd, Rd);
	V3_subtract(difference_Ro_Rs, Ro, Rs);
	B = 2 * V3_dot(Rd, difference_Ro_Rs);
	//B = V3_dot(Rd, difference_Ro_Rs);
	//C = V3_dot(difference_Ro_Rs, difference_Ro_Rs) - obj.radius * obj.radius;
	C = V3_dot(Rs, Rs) + V3_dot(Ro, Ro) - (V3_dot(Ro, Rs) * 2) - obj.radius * obj.radius;

	//double A = (Rd->i * Rd->i) + (Rd->j * Rd->j) + (Rd->z * Rd->z);
	//double B = 2 * (Rd->i * (0 - obj.position[0]) + 
	//	        Rd->j * (0 - obj.position[1]) + 
	//	        Rd->z * (0 - obj.position[2]));
	//double B = (2 * Rd->i * (0 - obj.position[0]) + 
	//	        2 * Rd->j * (0 - obj.position[1]) + 
	//	        2 * Rd->z * (0 - obj.position[2]));
	//double B = 2 * V3_dot(Rd, Ro);
	//double C = ((Rd->i - obj.position[0]) * (Rd->i - obj.position[0]) +
	//           (Rd->j - obj.position[1]) * (Rd->j - obj.position[1]) +
	//            (Rd->z - obj.position[2]) * (Rd->z - obj.position[2]) -
	//            (obj.radius * obj.radius));

	double discriminate = (B * B) - (4 * A * C);

	if(discriminate >= 0){
		distance_sqrt = sqrt(discriminate);
		t = (-0.5) * (B + distance_sqrt) / A;

		if(t > 0){
			return t;
		}
	}
	return 1000000000000.0;  // return infinity

	/*if(discriminate > 0){
		distance_sqrt = sqrt(discriminate);
		
		if(B < 0){
			q = (-B - distance_sqrt) / 2.0;
		} else {
			q = (-B + distance_sqrt) / 2.0;
		}
		
		t0 = q / A;
		t1 = C / q;

		// Swap if one is bigger than the other
		if(t0 < t1){
			temp = t1;
			t1 = t0;
			t0 = t1;
		}

		if(t1 >= 0){
			if(t0 < 0){
				return t1;
			} else {
				return t0;
			}
		}
	}

	return 1000000000000.0;  // return infinity
	*/
	//double intersect;
	//double intersect_1;
	//double intersect_2;
	//printf("B  = %f\nA  = %f\nC  = %f\n", B, A, C);
	//printf("discriminate - %f\n", discriminate);
	//if(discriminate < 0){
	//	return -1;
	//} else if(discriminate == 0){
	//	// Single intersection
	//	intersect = (-B)/(2 * A);
	//} else if(discriminate > 0){
	//	intersect_1 = ((-B - sqrt((B * B) - (4 * A * C))) / (2 * A));
	//	intersect_2 = ((-B + sqrt((B * B) - (4 * A * C))) / (2 * A));
	//	if(intersect_1 >= 0 && intersect_1 < intersect_2){
	//		intersect = intersect_1;
	//	} else {
	//		intersect = intersect_2;
	//	}
	//} else{
	//	printf("Error: sphere_intersection\n");
	//}

	//Compute intersection
	//V3 Ri = malloc(sizeof(V3));
	//Ri.i = 0 + (Rd->i * intersect);
	//Ri.j = 0 + (Rd->j * intersect);
	//Ri.z = 0 + (Rd->z * intersect);
	//printf("intersect - %f\n", intersect);
	//return intersect;
}

double intersect(V3 *Rd, scene_object obj){
	if(obj.kind == 0){  // Camera, should return a result that is never true
		double t = 1000000000000.0;  // infinity
		return t;
	}
	if(obj.kind == 1){  // Sphere
		double t = sphere_intersection(Rd, obj);
		return t;
	}
	if(obj.kind == 2){  // Plane
		double t = plane_intersection(Rd, obj);
		return t;
	}
}

Pixel * raycast(V3 *Rd, scene_object objects[], int obj_count){//Ro, Rd){
	// Camera Origin
	V3 *Ro = malloc(sizeof(V3));
	Ro->i = 0.0;
	Ro->j = 0.0;
	Ro->z = 0.0;

	Pixel *color = malloc(sizeof(Pixel));

	double t;
	double t_obj;
	scene_object closest_obj;
	scene_object obj;

	double closest_t = 1000000000000.0;  // infinity
	
	for(int i = 0; i < obj_count; i++){
		obj = objects[i];
		t_obj = intersect(Rd, obj);
		//printf("Current t = %f, kind = %d\n", t_obj, obj.kind);
		if(t_obj < t){
			t = t_obj;
			closest_obj = obj;
		}

		// Test for what kind of object it is
		//double t = intersection(Ro, Rd, obj);
		
		// For sphere, not just intersection, but sphere intersection
		// Code may replace code above
		//t_obj = intersect(Rd, obj);

		// Closest_obj == null?
		//if(t_obj < t){
		//	t = t_obj;
		//	closest_obj = obj;
		//}
	}
	//printf("%f\n", t);
	if(t == 1000000000000.0){  // infinity
		// Get color at the point of intersection
		// Convert 1.0 to 255 RGB
		int r = 0;
		int g = 0;
		int b = 0;
		// Convert int(4 bytes) to a char(1 byte)
		color->r = *((unsigned char *)&r);
		color->g = *((unsigned char *)&g);
		color->b = *((unsigned char *)&b);
		return color;  // no intersection
	}

	// Get point of intersection
	V3 *Ri = malloc(sizeof(V3));
	V3_add(Ri, Ro, Rd);
	V3_multiply(Ri, Ri, t);

	// Get color at the point of intersection
	// Convert 1.0 to 255 RGB
	int r = round(closest_obj.color[0] * 255);
	int g = round(closest_obj.color[1] * 255);
	int b = round(closest_obj.color[2] * 255);
	// Convert int(4 bytes) to a char(1 byte)
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
			//if(j % 10 == 0){
			//	printf("This Works Right ????????\n");
			//}
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