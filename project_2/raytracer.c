#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "parser.h"
#include "raycast.h"

int main(int argc, char *argv[]){
	// The main file that will run all of the functions for the raycaster
	// Main can't be in raycast.c since the main will conflict with test_main.c
	// used to run the tests I created
	printf("Still working on it\n");

	// Checks if the # of arguements is correct
	if (argc != 5) {
		printf("Error: Wrong input\n");
		return 1;
	}

	WIDTH = atoi(argv[1]);
	HEIGHT = atoi(argv[2]);

	FILE *fr = fopen(argv[3], "r");
	if (fr == NULL) {
		printf("Input file does not exist\n");
		return 1;
	}

	scene_object *result = malloc(sizeof(scene_object) * 10);

	
}