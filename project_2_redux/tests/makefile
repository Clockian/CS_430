VPATH+=../code

test: test_main.c test_raycast.c test_writer.c test_parser.c\
			raycast.c writer.c parser.c math3D.c\
			test_raycast.h test_writer.h test_parser.h\
			raycast.h writer.h parser.h math3D.h

	gcc -o ../test test_main.c test_raycast.c test_writer.c test_parser.c\
		../code/raycast.c ../code/writer.c ../code/parser.c ../code/math3D.c -lm

.PHONY: all test clean

clean:
	rm -f test *.o
