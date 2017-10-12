//begining of project
#include <stdlib.h>
#include <stdio.h>
#include "math3D.h"
#include "parser.h"

// Create function render(depends on whether or not you use global vars)
pixel * render(){
	Pixel *pixels = malloc(sizeof(double) * 3);
	for(int i = 0; i < width; i += 1){  // i from the Pij
		for(int j = 0; j < height; j += 1){
			//Pij = ... formula to construct Pij
			pixels = ;

			// Struct?
			V3_assign(Pij,
				  ...x,
				  ...y,
				  ...z);

			// Ray direction, not necessary to make a Ro variable
			V3_assign(Rd,
				  ...,
				  ...,
				  ...,);

			// Cast the ray
			color = raycast(Ro, Rd, ...);

			// Colors in ray tracers go from 0-1, RGB is 1-255, need conversion
			pixels[...] = color.red;
			pixels[...] = color.green;
			pixels[...] = color.blue;
		}
	}
}

void Raycast(Ro, Rd){
	cloest_obj = NULL;
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
	return closet_obj.color;
}

// Objects* objects or scene
// int object_counts;
*/

int main(int argc, char *argv[]){
	printf("this works, raytracer\n");
}
/* Garbage test code
	V3 c = {0, 0, 0};
	V3 a = {1, 2, 3};
	V3 b = {1, 2, 3};
	c = V3_add(c, a, b);
	printf("c.V0 -> %f, c.V1 -> %f, c.V2 -> %f\n", c.V0, c.V1, c.V2);

*/
