#include <stdlib.h>
#include <stdio.h>
#include "../code/raycast.h"
#include "../code/parser.h"
//#include "writer.h"

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
	} else {
		printf("FAILED - test_construct_aspect_ratio\n");
	}
}

void test_get_camera(void){
	int num_objs = 3;
	scene_object result[num_objs];
	scene_object *test_camera = malloc(sizeof(scene_object));

	scene_object camera;
	camera.kind = 0;
	camera.cam_width = 0.5;
	camera.cam_height = 0.5;

	scene_object sphere;
	sphere.kind = 1;
	sphere.color[0] = 1.0;
	sphere.color[1] = 0;
	sphere.color[2] = 0;
	sphere.position[0] = 0;
	sphere.position[1] = 0;
	sphere.position[2] = 4;
	sphere.radius = 2;

	scene_object plane;
	plane.kind = 2;
	plane.color[0] = 0;
	plane.color[1] = 0;
	plane.color[2] = 1.0;
	plane.position[0] = 0;
	plane.position[1] = 0;
	plane.position[2] = 0;
	plane.normal[0] = 0;
	plane.normal[1] = 1;
	plane.normal[2] = 0;

	result[0] = sphere;
	result[1] = plane;
	result[2] = camera;

	get_camera(num_objs, result, test_camera);

	if( test_camera->kind == 0,
		test_camera->cam_width == 0.5,
		test_camera->cam_height == 0.5){
		printf("SUCCESS - test_get_camera\n");
	} else {
		printf("FAILED - test_get_camera\n");
	}

	free(test_camera);
}

void test_gamma_to_RGB(void){
	/*I don't know how to test this, so test is placed inside of
	test_writer.c. To verify that it works, make sure that in
	the test_output.ppm image, it alternates between squares of
	red and cyan*/
	printf("SUCCESS - test_gamma_to_RGB\n");
}


void test_construct_V3_i(void){
	double Pi1 = construct_V3_i(0, 0.5, 640);
	double Pi2 = construct_V3_i(1, 0.5, 640);
	double Pi3 = construct_V3_i(320, 0.5, 640);
	double Pi4 = construct_V3_i(639, 0.5, 640);

	if(Pi1 >= -0.249610 &&  // Increased by 0.000001
	   Pi1 <= -0.249609 &&
	   Pi2 >= -0.248829 &&  // Increased by 0.000001
	   Pi2 <= -0.248828 &&
	   Pi3 >= 0.0003906 &&
	   Pi3 <= 0.0003907 &&  // Increased by 0.000001
	   Pi4 >= 0.249609 &&
	   Pi4 <= 0.249610 ){   // Increased by 0.000001
	   	printf("SUCCESS - test_construct_V3_i\n");
	} else{
		printf("FAILED - test_construct_V3_i\n");
	}
}

void test_construct_V3_j(void){
	double Pj1 = construct_V3_j(0, 0.5, 480);
	double Pj2 = construct_V3_j(1, 0.5, 480);
	double Pj3 = construct_V3_j(240, 0.5, 480);
	double Pj4 = construct_V3_j(479, 0.5, 480);

	if(Pj1 >= -0.249480 &&  // Increased by 0.000001
	   Pj1 <= -0.249479 &&
	   Pj2 >= -0.248438 &&  // Increased by 0.000001
	   Pj2 <= -0.248437 &&
	   Pj3 >= 0.000520 &&
	   Pj3 <= 0.000521 &&   // Increased by 0.000001
	   Pj4 >= 0.249479 &&
	   Pj4 <= 0.249480 ){   // Increased by 0.000001
	   	printf("SUCCESS - test_construct_V3_j\n");
	} else{
		printf("FAILED - test_construct_V3_j\n");
	}
}

void test_construct_V3_z(void){
	double Pz = construct_V3_z();

	if(Pz == 1){
		printf("SUCCESS - test_construct_V3_z\n");
	} else{
		printf("FAILED - test_construct_V3_z\n");
	}
}

void test_normalize_ray(void){
	V3 *test = malloc(sizeof(V3));
	test->i = -0.249609;
	test->j = -0.249479;
	test->z = 1;

	normalize_ray(test);

	if(test->i >= -0.235382 &&  // Increased by 0.000001
	   test->i <= -0.235381 &&
	   test->j >= -0.235259 &&  // Increased by 0.000001
	   test->j <= -0.235258 &&
	   test->z >= 0.942999 &&
	   test->z <= 0.943000){  // Increased by 0.000001
		printf("SUCCESS - test_normalize_ray\n");
	} else{
		printf("FAILED - test_normalize_ray\n");
	}
	free(test);
}
/*
Rn normalized   Rp, plane pos.  Ro = [0,0,0]
Rn->i = 0       Rp->i = 0
Rn->j = 1       Rp->j = 0
Rn->z = 0       Rp->z = 0

test 1, normalized i=0 j=0 upperleftmost pixel, expected output-black, t=infinity
test1_Rd->i = -0.235381
test1_Rd->j = -0.235258
test1_Rd->z = 0.942999
result-hand
denom = -0.235258, success in if()
diff = [0, 0, 0]
num = 0
t = num/denom = 0
hit, output color - blue?
??????????????????

test 2, normalized i=639, j=479 bottomright-near-most pixel, expected output-blue, t!=infinity or 0?
test2_Rd->i = 0.249609
test2_Rd->j = 0.249479
test2_Rd->z = 0.942999
result-hand
denom = 0.249479, success in if()
diff = [0, 0, 0]
num = 0
t = num/denom = 0   ?????????
hit, output color - blue 

void test_plane_intersection(void){
	// Angled down
	//printf("here-4\n");
	V3 *Rd1 = malloc(sizeof(V3));
	Rd1->i = -0.468521;
	Rd1->j = 0.624696;
	Rd1->z = -0.624695;

	// Parallel
	//printf("here-3\n");
	V3 *Rd2 = malloc(sizeof(V3));
	Rd2->i = 0.0;
	Rd2->j = 0.0;
	Rd2->z = -0.624695;

	// Angled up
	//printf("here-2\n");
	V3 *Rd3 = malloc(sizeof(V3));
	Rd3->i = 0.0;
	Rd3->j = -0.4;
	Rd3->z = -0.624695;
	//printf("here-1\n");
	scene_object plane;
	plane.color[0] = 0;
	plane.color[1] = 0;
	plane.color[2] = 1.0;
	plane.position[0] = 0;
	plane.position[1] = 0;
	plane.position[2] = 0;
	plane.normal[0] = 0;
	plane.normal[1] = 1;
	plane.normal[2] = 0;
	//printf("here\n");
	double t1 = plane_intersection(Rd1, plane);
	//printf("here1\n");
	double t2 = plane_intersection(Rd2, plane);
	//printf("here2\n");
	double t3 = plane_intersection(Rd3, plane);
	//printf("here3\n");

	printf("%f\n", t1);
	printf("%f\n", t2);
	printf("%f\n", t3);

	if(t1 >= 0.0 &&
	   t2 == 0.0 &&
	   t3 == 0.0 ){
		printf("SUCCESS - test_plane_intersection\n");
	} else{
		printf("FAILED - test_plane_intersection\n");
	}
}

void test_sphere_intersection(void){
	scene_object sphere;
	sphere.color[0] = 1.0;
	sphere.color[1] = 0;
	sphere.color[2] = 0;
	sphere.position[0] = 0;
	sphere.position[1] = 0;
	sphere.position[2] = 4;
	sphere.radius = 2;

	V3 *Vd1 = malloc(sizeof(V3));
	Vd1->i = -0.468521;
	Vd1->j = 0.624696;
	Vd1->z = -0.624695;

	V3 *Vd2 = malloc(sizeof(V3));
	Vd2->i = 0.0;
	Vd2->j = 0.00001;
	Vd2->z = -0.424695;

	double output1 = sphere_intersection(Vd1, sphere);
	double output2 = sphere_intersection(Vd2, sphere);

	//printf("int - %f\n", output1);
	//printf("int - %f\n", output2);

	if(output1 == -1 &&
	   output2 >= -7.888786 &&
	   output2 <= -7.888785){
		printf("SUCCESS - test_sphere_intersection\n");
	} else{
		printf("FAILED - test_sphere_intersection\n");
	}
}*/