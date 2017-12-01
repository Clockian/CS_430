#include <stdio.h>
#include <stdlib.h>
#include "../code/writer.h"
#include "../code/raycast.h"

void test_write_P6(void){
	FILE *fh = fopen("test_output.ppm", "w");

	int WIDTH = 160;
	int HEIGHT = 120;

	Color *pixmap;
	pixmap = malloc(sizeof(Color) * WIDTH * HEIGHT);

	int dx = WIDTH/2;
	int dy = HEIGHT/2;

	// Test for gamma_to_RGB to ensure that it changes color
	Color *color_red = malloc(sizeof(Color));
	Color *color_cyan = malloc(sizeof(Color));

	double r1 = 1.0;
	double g1 = 0;
	double b1 = 0;

	double r2 = 0;
	double g2 = 1.0;
	double b2 = 1.0;

	gamma_to_RGB(r1, g1, b1, color_red);
	gamma_to_RGB(r2, g2, b2, color_cyan);

	for(int row = 0; row < HEIGHT; row += 1){
		for(int col = 0; col < WIDTH; col += 1){
			if((row/dy + col/dx) % 2 == 0){
				pixmap[WIDTH * row + col].r = color_red->r;
				pixmap[WIDTH * row + col].g = color_red->g;
				pixmap[WIDTH * row + col].b = color_red->b;
			} else {
				pixmap[WIDTH * row + col].r = color_cyan->r;
				pixmap[WIDTH * row + col].g = color_cyan->g;
				pixmap[WIDTH * row + col].b = color_cyan->b;
			}
		}
	}

	write_P6(fh, pixmap, WIDTH, HEIGHT);

	printf("SUCCESS - test_write_P6\n");
	printf("Look at image in an imageviewer to check correctness.\n");
	printf("Image should be a checkerboard of Cyan and Red.\n");

	free(pixmap);
	free(color_red);
	free(color_cyan);
}