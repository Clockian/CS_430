#include <stdio.h>
#include <stdlib.h>
#include "raycast.h"

void test_construct_aspect_ratio(void){
	double ratio1 = construct_aspect_ratio(640, 480);
	double ratio2 = construct_aspect_ratio(900, 1500);
	double ratio3 = construct_aspect_ratio(1200, 1800);

	if(ratio1 >= 1.33333 &&
	   ratio1 <= 1.33334 &&
	   ratio2 == 0.6 &&
	   ratio3 >= 0.66666 &&
	   ratio3 <= 0.66667){
		printf("SUCCESS - test_construct_aspect_ratio\n");
	} else{
		printf("FAILED - test_construct_aspect_ratio\n");
	}
}

void test_construct_V3_i(void){
	double Pi1 = construct_V3_i(0, 640, 480);
	double Pi2 = construct_V3_i(1, 640, 480);
	double Pi3 = construct_V3_i(320, 640, 480);
	double Pi4 = construct_V3_i(639, 640, 480);

	if(Pi1 >= -0.750001 &&
	   Pi1 <= -0.750000 &&
	   Pi2 >= -0.747657 &&
	   Pi2 <= -0.747656 &&
	   Pi3 == 0 &&
	   Pi4 >= 0.747656 &&
	   Pi4 <= 0.747657
	   ){
	   	printf("SUCCESS - test_construct_V3_i\n");
	} else{
		printf("FAILED - test_construct_V3_i\n");
	}
}

void test_construct_V3_j(void){
	double Pj1 = construct_V3_j(0, 480);
	double Pj2 = construct_V3_j(1, 480);
	double Pj3 = construct_V3_j(240, 480);
	double Pj4 = construct_V3_j(479, 480);

	if(Pj1 == 1 &&
	   Pj2 >= 0.995833 &&
	   Pj2 <= 0.995834 &&
	   Pj3 == 0 &&
	   Pj4 >= -0.995834 &&
	   Pj4 <= -0.995833){
	   	printf("SUCCESS - test_construct_V3_j\n");
	} else{
		printf("FAILED - test_construct_V3_j\n");
	}
}

void test_construct_V3_z(void){
	double Pz = construct_V3_z();

	if(Pz == -1){
		printf("SUCCESS - test_construct_V3_z\n");
	} else{
		printf("FAILED - test_construct_V3_z\n");
	}
}

void test_construct_V3_i_j_z(void){
	V3 *test = construct_V3_i_j_z(0, 0, 640, 480);

	V3 result;
	result.i = -0.750000;
	result.j = 1;
	result.z = -1;

	if(test->i == result.i &&
	   test->j == result.j &&
	   test->z == result.z ){
		printf("SUCCESS - test_construct_V3_i_j_z\n");
	} else{
		printf("FAILED - test_construct_V3_i_j_z\n");
	}
}

void test_construct_ray_direction(void){
	V3 *input = malloc(sizeof(V3));
	input->i = -0.750000;
	input->j = 1;
	input->z = -1;

	V3 *test = construct_ray_direction(input);

	V3 result;
	result.i = -0.750000;
	result.j = 1;
	result.z = -1;

	if(test->i == result.i &&
	   test->j == result.j &&
	   test->z == result.z 
		){
		printf("SUCCESS - test_construct_ray_direction\n");
	} else{
		printf("FAILED - test_construct_ray_direction\n");
	}
}

void test_normalize_ray(void){
	V3 *input = malloc(sizeof(V3));
	input->i = -0.750000;
	input->j = 1;
	input->z = -1;

	V3 *test = normalize_ray(input);

	if(test->i >= -0.468522 &&
	   test->i <= -0.468521 &&
	   test->j >= 0.624695 &&
	   test->j <= 0.624696 &&
	   test->z >= -0.624696 &&
	   test->z <= -0.624695){
		printf("SUCCESS - test_normalize_ray\n");
	} else{
		printf("FAILED - test_normalize_ray\n");
	}
}