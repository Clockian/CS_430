#include <stdio.h>
#include <stdlib.h>
#include "writer.h"

void write_P6(FILE *fh, Pixel *pixmap, int width, int height){
	//fh = fopen("output.ppm", "w");
	fprintf(fh, "P6\n%d %d\n255\n", width, height);
	fwrite(pixmap, sizeof(Pixel), width*height,fh);
	fclose(fh);
}