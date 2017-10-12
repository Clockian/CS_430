#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

void test_remove_brackets_whitespace(){
	char *test_str = "sphere, color: [1.0, 0, 0], position: [0, 2, 5], radius: 2";
	char *test_result = "sphere,color:1.0,0,0,position:0,2,5,radius:2";
	
	char *output = remove_brackets_whitespace(test_str);

	if(strcmp(output, test_result) == 0){
		printf("SUCCESS - test_remove_brackets_whitespace\n");
	} else {
		printf("FAILED  - test_remove_brackets_whitespace\n");
	}
}

void test_parse(){
	char *test_str1 = "sphere,color:1.0,0,0,position:0,2,5,radius:2";
	char *test_str2 = "color:1.0,0,0,position:0,2,5,radius:2";
	char *test_str3 = "2";
	char *test_result1 = "sphere";
	char *test_result2 = "color";
	char *test_result3 = "2";

	char *output1 = parse(test_str1);
	char *output2 = parse(test_str2);
	char *output3 = parse(test_str3);

	if(strcmp(output1, test_result1) == 0 && 
	   strcmp(output2, test_result2) == 0 && 
	   strcmp(output3, test_result3) == 0){
		printf("SUCCESS - test_parse\n");
	} else {
		printf("FAILED  - test_parse\n");
	}
}

void test_cut_string(){
	char *test_str1 = "sphere,color:1.0,0,0,position:0,2,5,radius:2";
	char *test_result1 = "color:1.0,0,0,position:0,2,5,radius:2";
	char *test_str2 = "color:1.0,0,0,position:0,2,5,radius:2";
	char *test_result2 = "1.0,0,0,position:0,2,5,radius:2";
	char *test_str3 = "radius:2";
	char *test_result3 = "2";

	char *output1 = cut_string(test_str1);
	char *output2 = cut_string(test_str2);
	char *output3 = cut_string(test_str3);

	if(strcmp(output1, test_result1) == 0 &&
	   strcmp(output2, test_result2) == 0 &&
	   strcmp(output3, test_result3) == 0){
		printf("SUCCESS - test_cut_string\n");
	} else {
		printf("FAILED  - test_cut_string\n");
	}
}

void test_determine_type(){
	char *test_str = "camera,width:0.5,height:0.5";
	
	scene_object *test_obj;
	test_obj = determine_type(test_str);

	scene_object result_obj;
	result_obj.kind = 0;
	result_obj.cam_width = 0.5;
	result_obj.cam_height = 0.5;

	if(test_obj->kind == result_obj.kind &&
	   test_obj->cam_width == result_obj.cam_width &&
	   test_obj->cam_height == result_obj.cam_height){
		printf("SUCCESS - test_determine_type\n");
	} else {
		printf("FAILED  - test_determine_type\n");
	}
}

void test_parse_camera(){
	char *test_str = "width:0.5,height:0.5";
	
	scene_object *test_obj;
	test_obj = parse_camera(test_str);

	scene_object result_obj;
	result_obj.kind = 0;
	result_obj.cam_width = 0.5;
	result_obj.cam_height = 0.5;

	if(test_obj->kind == result_obj.kind &&
	   test_obj->cam_width == result_obj.cam_width &&
	   test_obj->cam_height == result_obj.cam_height){
		printf("SUCCESS - test_parse_camera\n");
	} else {
		printf("FAILED  - test_parse_camera\n");
	}
}

void test_parse_sphere(){
	char *test_str = "color:1.0,0,0,position:0,2,5,radius:2";
	
	scene_object *test_obj;
	test_obj = parse_sphere(test_str);

	scene_object result_obj;
	result_obj.kind = 1;
	result_obj.color[0] = 1.0;
	result_obj.color[1] = 0;
	result_obj.color[2] = 0;
	result_obj.position[0] = 0;
	result_obj.position[1] = 2;
	result_obj.position[2] = 5;
	result_obj.radius = 2;

	if(test_obj->kind == result_obj.kind &&
	   test_obj->color[0] == result_obj.color[0] &&
	   test_obj->color[1] == result_obj.color[1] &&
	   test_obj->color[2] == result_obj.color[2] &&
	   test_obj->position[0] == result_obj.position[0] &&
	   test_obj->position[0] == result_obj.position[0] &&
	   test_obj->position[0] == result_obj.position[0] &&
	   test_obj->radius == result_obj.radius){
		printf("SUCCESS - test_parse_sphere\n");
	} else {
		printf("FAILED  - test_parse_sphere\n");
	}
}

void test_parse_plane(){
	char *test_str = "color:0,0,1.0,position:0,0,0,normal:0,1,0";
	
	scene_object *test_obj;
	test_obj = parse_plane(test_str);

	scene_object result_obj;
	result_obj.kind = 2;
	result_obj.color[0] = 0;
	result_obj.color[1] = 0;
	result_obj.color[2] = 1.0;
	result_obj.position[0] = 0;
	result_obj.position[1] = 0;
	result_obj.position[2] = 0;
	result_obj.normal[0] = 0;
	result_obj.normal[1] = 1;
	result_obj.normal[2] = 0;

	if(test_obj->kind == result_obj.kind &&
	   test_obj->color[0] == result_obj.color[0] &&
	   test_obj->color[1] == result_obj.color[1] &&
	   test_obj->color[2] == result_obj.color[2] &&
	   test_obj->position[0] == result_obj.position[0] &&
	   test_obj->position[1] == result_obj.position[1] &&
	   test_obj->position[2] == result_obj.position[2] &&
	   test_obj->normal[0] == result_obj.normal[0] &&
	   test_obj->normal[1] == result_obj.normal[1] &&
	   test_obj->normal[2] == result_obj.normal[2]){
		printf("SUCCESS - test_parse_plane\n");
	} else {
		printf("FAILED  - test_parse_plane\n");
	}
}

void test_read_csv_file(){
	scene_object result[4];
	FILE *fr = fopen("input.csv", "r");
	read_csv_file(fr, result);

	if(result[0].kind == 0 &&
	   result[0].cam_width == 0.5 &&
	   result[0].cam_height == 0.5 &&
	   result[1].kind == 1 &&
	   result[1].color[0] == 1.0 &&
	   result[1].color[1] == 0 &&
	   result[1].color[2] == 0 &&
	   result[1].position[0] == 0 &&
	   result[1].position[1] == 2 &&
	   result[1].position[2] == 5 &&
	   result[1].radius == 2 &&
	   result[2].color[0] == 0 &&
	   result[2].color[1] == 0 &&
	   result[2].color[2] == 1.0 &&
	   result[2].position[0] == 0 &&
	   result[2].position[1] == 0 &&
	   result[2].position[2] == 0 &&
	   result[2].normal[0] == 0 &&
	   result[2].normal[1] == 1 &&
	   result[2].normal[2] == 0){
		printf("SUCCESS - test_test_read_csv_file\n");
	} else {
		printf("FAILED  - test_test_read_csv_file\n");
	}
}

int main(){
	test_remove_brackets_whitespace();
	test_parse();
	test_cut_string();
	test_determine_type();
	test_parse_camera();
	test_parse_sphere();
	test_parse_plane();
	test_read_csv_file();

	return 0;
}