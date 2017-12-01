#ifndef WRITER_H
#define WRITER_H

typedef struct Color{
	unsigned char r, g, b;
}Color;

void write_P6(FILE *fh, Color *pixmap, int width, int height);

#endif /* WRITER_H */