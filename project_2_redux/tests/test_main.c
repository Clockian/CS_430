#include <stdio.h>
#include <stdlib.h>
#include "test_parser.h"
#include "test_raycast.h"
#include "test_writer.h"

int main(){
	test_remove_brackets_whitespace();
	test_parse();
	test_cut_string();
	test_determine_type();
	test_parse_camera();
	test_parse_sphere();
	test_parse_plane();
	test_get_num_lines();
	test_read_csv_file();

	printf("\n");

	test_construct_aspect_ratio();
	test_get_camera();
	test_construct_V3_i();
	test_construct_V3_j();
	test_construct_V3_z();
	test_normalize_ray();
	//test_plane_intersection();
	//test_sphere_intersection();

	printf("\n");

	test_gamma_to_RGB();
	test_write_P6();

	return 0;
}
