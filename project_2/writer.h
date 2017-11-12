#ifndef WRITER_H
#define WRITER_H

typedef struct Pixel{
	unsigned char r, g, b;
}Pixel;

void write_P6(FILE *fh, Pixel *pixmap, int width, int height);

#endif /* WRITER_H */