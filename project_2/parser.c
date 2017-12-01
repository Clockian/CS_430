#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
/*
 *  Given a string, it will remove all spaces and brackets
 */
char * remove_brackets_whitespace(char *str) {
	// Determine the number of chars that need to be removed for malloc so str can
	// be returned without being deallocated
	char *str_iterate = str;
	int num_rmchar = 0;
	while(*str_iterate != '\0') {
		if(*str_iterate == ' ' || *str_iterate == '[' || *str_iterate == ']') {
			num_rmchar++;
			str_iterate++;
		} else {
			str_iterate++;
		}
	}

	int str_len = strlen(str);

	// Adds one to account for the null, minus the num of chars we intend to rm
	char *output = malloc(sizeof(char) * str_len + 1 - num_rmchar);

	// Remove ',' '[' ']', and transfer contents of str to new str
	char *output_iterate = output;
	while(*str != '\0'){
		if(*str == ' ' || *str == '[' || *str == ']') {
			str++;
		} else {
			*output_iterate = *str;
			str++;
			output_iterate++;
		}
	}

	return output;
}

/*
 *  Given a string w/o spaces or brackets, returns a new string up to next ',', '\0' or ':'
 */
char * parse(char *str) {
	// Find location of comma so we can allocate the right memory to return char*
	char *str_iterate = str;
	int str_len = 0;
	while(*str_iterate != ',' && *str_iterate != ':' && *str_iterate != '\0'){
		str_len++;
		str_iterate++;
	}

	char *output = malloc(sizeof(char) * str_len);

	// Transfer contents to char* to be returned
	char *output_iterate = output;
	while(*str != ',' && *str != ':' && *str != '\0'){
		*output_iterate = *str;
		str++;
		output_iterate++;
	}

	return output;
}

/*
 *  Given a string w/o spaces or brackets, returns the remainder of the 
 *  string after the first comma found
 *  Do not cut string that will have nothing for the remainder, as it will cause
 *  a Segmentation Fault, EX: Success: "radius:2" -> "2", Fail: "2" -> Segmentation Fault
 */
char * cut_string(char *str) {
	// Find location of ',', ':', or null to allocate the right memory to return char*
	int total_str_len = strlen(str);
	char *str_iterate = str;
	int str_len = 0;
	while(*str_iterate != ',' && *str_iterate != ':' && *str_iterate != '\0'){
		str_len++;
		str_iterate++;
	}
	str_len++;  // To have the length include the comma

	char *output = malloc(sizeof(char) * total_str_len - str_len);

	// Transfer contents to char* to be returned
	char *output_iterate = output;
	str = str + str_len;  // Skip the contents up to first comma
	while(*str != '\0'){
		*output_iterate = *str;
		str++;
		output_iterate++;
	}

	return output;
}

/*
 *  Given a string and a obj in the scene, determine the type and how the rest of 
 *  the data is to be read
 */
scene_object * determine_type(char *str) {
	char *str_cleaned = remove_brackets_whitespace(str);
	char *type = parse(str_cleaned);
	char *remainder = cut_string(str_cleaned);

	if(strcmp(type, "camera") == 0){
		scene_object *obj = parse_camera(remainder);
		return obj;
	} else if(strcmp(type, "sphere") == 0){
		scene_object *obj = parse_sphere(remainder);
		return obj;
	} else if(strcmp(type, "plane") == 0){
		scene_object *obj = parse_plane(remainder);
		return obj;
	} else{
		printf("Error: Invalid input in CSV\n");
	}
}

/*
 *  Given a cleaned str w/o the type, pulls out the data for the camera into a
 *  struct and returns it
 */
scene_object * parse_camera(char *str) {
	scene_object *obj = malloc(sizeof(scene_object));
	obj->kind = 0;

	char *data_type = parse(str);
	char *remainder = cut_string(str);
	for(int ii = 0; ii < 2; ii++){
		if(strcmp(data_type, "width") == 0){
			char *width_data = parse(remainder);
			double width_num = atof(width_data);
			obj->cam_width = width_num;
		} else if(strcmp(data_type, "height") == 0){
			char *height_data = parse(remainder);
			double height_num = atof(height_data);
			obj->cam_height = height_num;
		} else {
			printf("Error:parse_camera: Bad input for camera entry\n");
		}
		
		if(ii != 1){
			remainder = cut_string(remainder);  // Cut of number we just used
			data_type = parse(remainder);
			remainder = cut_string(remainder);
		}
	}
	return obj;
}

/*
 *  Given a cleaned str w/o the type, pulls out the data for the sphere into a
 *  struct and returns it
 */
scene_object * parse_sphere(char *str) {
	scene_object *obj = malloc(sizeof(scene_object));
	obj->kind = 1;

	char *data_type = parse(str);
	char *remainder = cut_string(str);

	for(int ii = 0; ii < 3; ii++){
		if(strcmp(data_type, "color") == 0){
			for(int jj = 0; jj < 3; jj++){
				char *color_data = parse(remainder);
				double color_num = atof(color_data);
				obj->color[jj] = color_num;
				if(jj != 2){
					remainder = cut_string(remainder);
				}
			}
		} else if(strcmp(data_type, "position") == 0){
			for(int jj = 0; jj < 3; jj++){
				char *position_data = parse(remainder);
				double position_num = atof(position_data);
				obj->position[jj] = position_num;
				if(jj != 2){
					remainder = cut_string(remainder);
				}
			}
		} else if(strcmp(data_type, "radius") == 0){
			char *radius_data = parse(remainder);
			double radius_num = atof(radius_data);
			obj->radius = radius_num;
		} else {
			printf("Error:parse_sphere: Bad input for sphere entry\n");
		}
		
		if(ii != 2){
			remainder = cut_string(remainder);  // Cut of number we just used
			data_type = parse(remainder);
			remainder = cut_string(remainder);
		}
	}
	return obj;
}

/*
 *  Given a cleaned str w/o the type, pulls out the data for the sphere into a
 *  struct and returns it
 */
scene_object * parse_plane(char *str) {
	scene_object *obj = malloc(sizeof(scene_object));
	obj->kind = 2;

	char *data_type = parse(str);
	char *remainder = cut_string(str);

	for(int ii = 0; ii < 3; ii++){
		if(strcmp(data_type, "color") == 0){
			for(int jj = 0; jj < 3; jj++){
				char *color_data = parse(remainder);
				double color_num = atof(color_data);
				obj->color[jj] = color_num;
				if(jj != 2){
					remainder = cut_string(remainder);
				}
			}
		} else if(strcmp(data_type, "position") == 0){
			for(int jj = 0; jj < 3; jj++){
				char *position_data = parse(remainder);
				double position_num = atof(position_data);
				obj->position[jj] = position_num;
				if(jj != 2){
					remainder = cut_string(remainder);
				}
			}
		} else if(strcmp(data_type, "normal") == 0){
			for(int jj = 0; jj < 3; jj++){
				char *normal_data = parse(remainder);
				double normal_num = atof(normal_data);
				obj->normal[jj] = normal_num;
				if(jj != 2){
					remainder = cut_string(remainder);
				}
			}
		} else {
			printf("Error:parse_normal: Bad input for normal entry\n");
		}
		
		if(ii != 2){
			remainder = cut_string(remainder);  // Cut of number we just used
			data_type = parse(remainder);
			remainder = cut_string(remainder);
		}
	}
	return obj;
}

int get_num_lines(FILE *fr){
	char str[100];
	int ii = 0;
	while(fgets(str, 99, fr)){
		ii++;
	}
	return ii;
}

/*
 *  Given an open CSV file, and an array, it will pull every scene object out of
 *  the data file and put it into the array, which can then be used
 */
void read_csv_file(FILE *fr, scene_object result[]) {
	char str[100];
	int ii = 0;
	scene_object *obj;

	while(fgets(str, 99, fr)){
		char *cleaned_str = remove_brackets_whitespace(str);
		obj = determine_type(cleaned_str);

		result[ii] = *obj;
		ii++;
	}
}