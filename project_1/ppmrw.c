#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

	// Checks if the # of arguements is correct
	if (argc != 4) {
		printf("Usage: ppmrw CONVERT-TO-# INPUT-FILE OUTPUT-FILE\n");
		return 1;
	}

	// Check if arg 1 is a 3 or 6
	

	// Check file names to see if they
	// 	-End in .ppm
	// 	-input and output filename are different
	// 	-No negative "-" at the beginning
	

	// Read input file into memory, else it can't be read from
	

	// Read "magic number" in the file for P3 or P6
	

	// Skip any comments "#" to get the "HEIGHT WIDTH"
	

	// Skip any comment "#" to get the RGB max color value
	

	// If converting from P3 to P6, change the ASCII decimal to binary
	

	// If converting from P6 to P3, convert the binary to ASCII decimal
