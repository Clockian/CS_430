CC = gcc
CFLAGS = -O -wall -wextra

all: raytracer.c raycast.c parser.c writer.c math3D.c\
		raycast.h parser.h writer.h math3D.h

	gcc raytracer.c raycast.c parser.c writer.c math3D.c\
		-o ../raycast -lm

clean:
	rm -rf raycast *~
