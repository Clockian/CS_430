//begining of project
#include <stdlib.h>
#include <stdio.h>
int main(){
	printf("this renders");
}
/*
// Create function render(depends on whether or not you use global vars)
pixel*  render(){
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

// Parser CSV
// Take in by line and break up, or accept term by term. Problably latter

// Have one for plane, sphere, camera
// Poor man's polymorphism
// Cheat, put everything into one struct

typedef struct{
	int kind;
	position;
	color;
	double radius;
	//plane
	normal;
	camera;
	width;
	height;
}

// problably need obj as parameter
parse_type(...){
	// read till you get a comma
	//if string is == to strcmp(str, "camera"{
	//	obj -> kind = camera;
	//}
	//... each type
	//

parse_field(..., obj){
	// Read till colon
	// ster = read until colon
	// if strcmp(str, "position")
	// parse_position;
	// ... each field type
	//}
	//

parse_radius(...obj){
	// skip_ws(); skip whitespace
	// fscanf("%"..., &value);
	// obj-radius = value;
	// for each of the field types
	//
}
*/
// Objects* objects or scene
// int object_counts;
