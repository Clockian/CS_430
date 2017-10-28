#include <stdio.h>
#include <stdlib.h>
#include "writer.h"

void write_P6(FILE *fh, Pixel *pixmap, int width, int height){
	fprintf(fh, "P6\n%d %d\n255\n", width, height);
	fwrite(pixmap, sizeof(Pixel), width*height,fh);
	fclose(fh);
}