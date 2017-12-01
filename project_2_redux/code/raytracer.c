#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "parser.h"
#include "raycast.h"

int main(int argc, char *argv[]){
	// The main file that will run all of the functions for the raycaster
	// Main can't be in raycast.c since the main will conflict with test_main.c
	// used to run the tests I created

	// Checks if the # of arguements is correct
	if (argc != 5) {
		printf("Error: Wrong input\n");
		return 1;
	}

	int pixel_width = atoi(argv[1]);
	int pixel_height = atoi(argv[2]);

	FILE *fr = fopen(argv[3], "r");
	if (fr == NULL) {
		printf("Input file does not exist\n");
		return 1;
	}

	int num_objs = get_num_lines(fr);

	scene_object result[num_objs];  // num_objs

	FILE *fr2 = fopen(argv[3], "r");

	read_csv_file(fr2, result);

	Color *pixmap = malloc(sizeof(Color) * pixel_width * pixel_height);

	pixmap = render(pixel_width, pixel_height, result, num_objs, pixmap);

	FILE *fw = fopen(argv[4], "w");

	write_P6(fw, pixmap, pixel_width, pixel_height);

	free(pixmap);
}