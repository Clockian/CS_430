#include <stdio.h>
#include <stdlib.h>
#include "writer.h"

void test_write_P6(void){
	FILE *fh = fopen("output.ppm", "w");

	int WIDTH = 640;
	int HEIGHT = 480;

	Pixel *pixmap;
	pixmap = malloc(sizeof(Pixel) * WIDTH * HEIGHT);

	int dx = WIDTH/8;
	int dy = HEIGHT/8;

	for(int row = 0; row < HEIGHT; row += 1){
		for(int col = 0; col < WIDTH; col += 1){
			if((row/dy + col/dx) % 2){
				pixmap[WIDTH * row + col].r = 255;
				pixmap[WIDTH * row + col].g = 0;
				pixmap[WIDTH * row + col].b = 0;
			} else {
				pixmap[WIDTH * row + col].r = 0;
				pixmap[WIDTH * row + col].g = 255;
				pixmap[WIDTH * row + col].b = 255;
			}
		}
	}

	write_P6(fh, pixmap, WIDTH, HEIGHT);

	printf("SUCCESS - test_write_P6\n");
	printf("Look at image in an imageviewer to check correctness.\n");
	printf("Image should be a checkerboard of Cyan and Red.\n");
}